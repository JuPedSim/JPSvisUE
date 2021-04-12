// Fill out your copyright notice in the Description page of Project Settings.


#include "Cache.h"
#include "../FileReaders/TrajectoryFileReader.h"

std::mutex accessMutex;

Cache::Cache(int bitsAssociativeness, int bitsIndex, int bitsWordOffset, std::string filePath)
{
	m_bitsAssociativeness = bitsAssociativeness;
	m_bitsIndex = bitsIndex;
	m_bitsWordOffset = bitsWordOffset;
	m_filePath = filePath;
	m_nextLRUid = 0;
	m_frameCount = TrajectoryFileReader::GetFrames(m_filePath);

	SetMasks();

	m_cacheLines.resize(pow(2, m_bitsIndex));
	for (auto& indexed : m_cacheLines)
	{
		int size = pow(2, m_bitsAssociativeness);
		indexed.resize(size);
		for (int i = 0;i<size;i++)
		{
			indexed.at(i) = CacheLine();
		}
	}
}

Cache::Cache()
{
	
}

CacheEntry Cache::GetCacheEntry(int address)
{
	if (address<0)
	{
		throw std::invalid_argument("received negative address");
	}

	int wordOffset = computeWordOffset(address);
	int index = computeIndex(address);
	int tag = computeTag(address);

	accessMutex.lock();
	int pos = GetPosition(index,tag);
	if (pos>=0) 
	{
		auto& line = m_cacheLines.at(index).at(pos);
		line.SetLruID(m_nextLRUid++);
		accessMutex.unlock();
		return line.GetEntry(wordOffset);
	}
	else
	{
		CacheEntry temp = m_cacheLines.at(index).at(LoadCacheLineAndReturnPos(index, tag)).GetEntry(wordOffset);
		accessMutex.unlock();
		return temp;
	}
}

void Cache::LoadCacheEntryAsync(int address)
{
	//
	//	needs rework with queua and only one loader thread 
	// 
	// 
	//int index = computeIndex(address);
	//int tag = computeTag(address);
	//if (GetPosition(index, tag)<0)
	//{
	//	//std::thread t(&Cache::LoadCacheLineAsync,this,index,tag);//todo does not work so simple (if address=5 is loading, address=4 might not need to load but thread for it is started anyway).  Also lock locks too much (Reading from file) and no performance increase
	//}
}

Cache::~Cache()
{
}

const int Cache::GetFramesCount()
{
	return m_frameCount;
}

int Cache::GetPosition(int index,int tag)
{
	for (int i = 0;i<m_cacheLines.at(index).size();i++) 
	{
		auto& line = m_cacheLines.at(index).at(i);
		if (line.GetIsValid() && line.GetTag() == tag)
		{
			return i;
		}
	}
	return -1;
}

int Cache::LoadCacheLineAndReturnPos(int index, int tag)
{
	int startAddress = (tag << (m_bitsIndex + m_bitsWordOffset)) | (index << m_bitsWordOffset);
	CacheLine newCacheLine = TrajectoryFileReader::LoadCacheLine(startAddress, pow(2, m_bitsWordOffset), m_filePath, tag, m_nextLRUid++);
	int pos = 0;
	unsigned int min = MAX_uint32;
	for (int i = 0; i < m_cacheLines.at(index).size(); i++)
	{
		if (m_cacheLines.at(index).at(i).GetIsValid())
		{
			unsigned int lruID = m_cacheLines.at(index).at(i).GetLruID();
			if (lruID < min)
			{
				min = lruID;
				pos = i;
			}
		}
		else
		{
			pos = i;
			break;
		}
	}
	m_cacheLines.at(index).at(pos) = newCacheLine;
	return pos;
}

void Cache::LoadCacheLineAsync(int index, int tag)
{
	accessMutex.lock();
	LoadCacheLineAndReturnPos(index, tag);
	accessMutex.unlock();
}

int Cache::computeIndex(int address)
{
	return (address & m_bitMaskIndex) >> m_bitsWordOffset;
}

int Cache::computeWordOffset(int address)
{
	return address & m_bitMaskWordOffset;
}

int Cache::computeTag(int address)
{
	return (address & m_bitMaskTag) >> (m_bitsWordOffset + m_bitsIndex);
}



void Cache::SetMasks()
{
	int bitMaskIndex = 0;
	for (int i = 0; i < m_bitsIndex; i++)
	{
		bitMaskIndex = bitMaskIndex | 1;
		if (i < m_bitsIndex - 1)
		{
			bitMaskIndex = bitMaskIndex << 1;
		}
	}
	m_bitMaskIndex = bitMaskIndex << m_bitsWordOffset;

	int bitMaskWordOffset = 0;
	for (int i = 0; i < m_bitsWordOffset; i++)
	{
		bitMaskWordOffset = bitMaskWordOffset | 1;
		if (i < m_bitsWordOffset - 1)
		{
			bitMaskWordOffset = bitMaskWordOffset << 1;
		}
	}
	m_bitMaskWordOffset = bitMaskWordOffset;

	int bitMaskTag = 0;
	int bitsTag = 32 - m_bitsWordOffset - m_bitsIndex;
	for (int i = 0; i < bitsTag; i++)
	{
		bitMaskTag = bitMaskTag | 1;
		if (i < bitsTag - 1)
		{
			bitMaskTag = bitMaskTag << 1;
		}
	}
	m_bitMaskTag = bitMaskTag<<(m_bitsWordOffset+ m_bitsIndex);
}
