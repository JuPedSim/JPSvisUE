// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <vector>
#include "../FileReaders/TrajectoryFileReader.h"
#include "CacheLine.h"
#include "CacheEntry.h"
#include <stdexcept>

/**
 * 
 */
class JPSVISUE_API Cache
{
public:
	Cache(int bitsAssociativeness, int bitsIndex, int bitsWordOffset,std::string filePath);
	Cache();
	CacheEntry GetCacheEntry(int address);
	~Cache();
	const int GetFramesCount();
private:
	int m_bitsAssociativeness;
	int m_bitsIndex;
	int m_bitsWordOffset;
	int m_bitMaskIndex;
	int m_bitMaskWordOffset;
	int m_bitMaskTag;
	int m_frameCount;
	unsigned int m_nextLRUid;
	std::string m_filePath;
	void SetMasks();
	std::vector<std::vector<CacheLine>> m_cacheLines;
};
