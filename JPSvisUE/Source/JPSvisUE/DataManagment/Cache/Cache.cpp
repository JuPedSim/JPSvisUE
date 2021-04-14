// Fill out your copyright notice in the Description page of Project Settings.


#include "Cache.h"
#include "../FileReaders/TrajectoryFileReader.h"
#include "CacheAsyncLoader.h"

std::mutex cacheLinesMutex;
std::mutex queueToLoadMutex;
std::mutex readFileMutex;

Cache::Cache(int bitsAssociativeness, int bitsIndex, int bitsWordOffset, std::string filePath)
{
	m_bitsAssociativeness = bitsAssociativeness;
	m_bitsIndex = bitsIndex;
	m_bitsWordOffset = bitsWordOffset;
	m_filePath = filePath;
	m_nextLRUid = 0;
	m_frameCount = TrajectoryFileReader::GetFrames(m_filePath);
	m_toLoadQueueHasLength = false;
	m_toLoadQueue.resize(0);

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

	m_threadIsRunning = false;
}

Cache::Cache()
{
	
}

CacheEntry Cache::LoadCacheEntrySync(int address)
{
	if (address<0)
	{
		throw std::invalid_argument("received negative address");
	}

	int wordOffset = ComputeWordOffset(address);
	int index = ComputeIndex(address);
	int tag = ComputeTag(address);

	cacheLinesMutex.lock();
	int pos = GetPosition(index,tag);
	if (pos>=0) 
	{
		auto line = m_cacheLines.at(index).at(pos);
		m_cacheLines.at(index).at(pos).SetLruID(m_nextLRUid++);
		cacheLinesMutex.unlock();
		UE_LOG(LogTemp, Warning, TEXT("Hit"));
		return line.GetEntry(wordOffset);
	}
	else
	{
		CacheEntry temp = LoadCacheLine(index, tag).GetEntry(wordOffset);
		cacheLinesMutex.unlock();
		UE_LOG(LogTemp, Warning, TEXT("Miss"));
		return temp;
	}
}

void Cache::LoadCacheEntryAsync(int address)
{
	if (!m_threadIsRunning)
	{
		std::shared_ptr<Cache> pointer(this);
		(new FAutoDeleteAsyncTask<CacheAsyncLoader>(pointer))->StartBackgroundTask();
		m_threadIsRunning = true;
	}

	int index = ComputeIndex(address);
	int tag = ComputeTag(address);
	if (GetPosition(index, tag)<0)
	{
		int startAdress = ComputeStartAdress(index, tag);
		bool alreadyInQueue = false;
		queueToLoadMutex.lock();
		for (int i = 0;i< m_toLoadQueue.size();i++)
		{
			if (m_toLoadQueue.at(i).address== startAdress)
			{
				alreadyInQueue = true;
			}
		}
		queueToLoadMutex.unlock();

		if (!alreadyInQueue) 
		{
			LoadJob toLoad;
			toLoad.address = startAdress;

			queueToLoadMutex.lock();
			m_toLoadQueue.push_back(toLoad);
			m_toLoadQueueHasLength = true;
			queueToLoadMutex.unlock();
		}
	}
}

Cache::~Cache()
{
}

const int Cache::GetFramesCount()
{
	return m_frameCount;
}

void Cache::CheckToLoad()
{
	LoadJob toLoad;
	bool hasJob = false;
	if (m_toLoadQueueHasLength)
	{
		queueToLoadMutex.lock();
		if (m_toLoadQueue.size() >= 1)
		{
			toLoad = m_toLoadQueue.at(m_toLoadQueue.size()-1);
			m_toLoadQueue.pop_back();
			if (m_toLoadQueue.size()==0)
			{
				m_toLoadQueueHasLength = false;
			}
			hasJob = true;
		}
		queueToLoadMutex.unlock();
	}
	if (hasJob) 
	{
		int index = ComputeIndex(toLoad.address);
		int tag = ComputeTag(toLoad.address);
		LoadCacheLineAndReturnPos(index, tag);
	}
	
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

int Cache::ComputeStartAdress(int index, int tag)
{
	return (tag << (m_bitsIndex + m_bitsWordOffset)) | (index << m_bitsWordOffset);;
}

int Cache::LoadCacheLineAndReturnPos(int index, int tag)
{
	int startAddress = ComputeStartAdress(index,tag);
	readFileMutex.lock();
	CacheLine newCacheLine = TrajectoryFileReader::LoadCacheLine(startAddress, pow(2, m_bitsWordOffset), m_filePath, tag, m_nextLRUid++);
	readFileMutex.unlock();
	int pos = 0;
	unsigned int min = MAX_uint32;
	cacheLinesMutex.lock();
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
	cacheLinesMutex.unlock();
	return pos;
}

CacheLine Cache::LoadCacheLine(int index, int tag)
{
	int startAddress = ComputeStartAdress(index, tag);
	readFileMutex.lock();
	CacheLine newCacheLine = TrajectoryFileReader::LoadCacheLine(startAddress, pow(2, m_bitsWordOffset), m_filePath, tag, m_nextLRUid++);
	readFileMutex.unlock();
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
	return newCacheLine;
}

int Cache::ComputeIndex(int address)
{
	return (address & m_bitMaskIndex) >> m_bitsWordOffset;
}

int Cache::ComputeWordOffset(int address)
{
	return address & m_bitMaskWordOffset;
}

int Cache::ComputeTag(int address)
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
