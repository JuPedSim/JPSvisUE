// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <vector>
#include <stdexcept>
#include "CacheLine.h"
#include "CacheEntry.h"
#include <mutex>
#include <thread>

/**
 * 
 */
class JPSVISUE_API Cache
{
public:
	Cache(int bitsAssociativeness, int bitsIndex, int bitsWordOffset,std::string filePath);
	Cache();
	CacheEntry GetCacheEntry(int address);
	void LoadCacheEntryAsync(int address);
	~Cache();
	const int GetFramesCount();
private:
	int GetPosition(int index, int tag);
	int LoadCacheLineAndReturnPos(int index, int tag);
	void LoadCacheLineAsync(int index, int tag);
	int computeIndex(int address);
	int computeWordOffset(int address);
	int computeTag(int address);
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
