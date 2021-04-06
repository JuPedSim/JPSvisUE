// Fill out your copyright notice in the Description page of Project Settings.


#include "Cache.h"



Cache::Cache(int bitsAssociativeness, int bitsIndex, int bitsWordOffset, std::string filePath)
{
	m_bitsAssociativeness = bitsAssociativeness;
	m_bitsIndex = bitsIndex;
	m_bitsWordOffset = bitsWordOffset;
	m_filePath = filePath;
	m_nextLRUid = 0;

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

	int wordOffset = address & m_bitsWordOffset;
	int index = (address & m_bitMaskIndex) >> m_bitsWordOffset;
	int tag = (address & m_bitMaskTag) >> (m_bitsWordOffset+m_bitsIndex);


	for(auto &line: m_cacheLines.at(index))
	{
		if (line.GetIsValid() && line.GetTag()==tag)
		{
			line.SetLruID(m_nextLRUid++);
			return line.GetEntry(wordOffset);
		}
	}

	int startAddress = (tag << (m_bitsIndex + m_bitsWordOffset)) | (index << m_bitsWordOffset);
	CacheLine newCacheLine = TrajectoryFileReader::LoadCacheLine(startAddress, pow(2, m_bitsWordOffset), m_filePath,tag, m_nextLRUid++);
	int pos = 0;
	unsigned int min = MAX_uint32;
	for (int i = 0;i<m_cacheLines.size();i++) 
	{
		unsigned int lruID = m_cacheLines.at(index).at(i).GetLruID();
		if (lruID < min)
		{
			min = lruID;
			pos = i;
		}
	}
	m_cacheLines.at(index).at(pos) = newCacheLine;
	CacheEntry temp = newCacheLine.GetEntry(wordOffset);
	return temp;
}

Cache::~Cache()
{
}

int Cache::GetFramesCount()
{
	return TrajectoryFileReader::GetFrames(m_filePath);
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
