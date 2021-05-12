// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <vector>
#include <stdexcept>
#include "CacheLine.h"
#include "../FileReaders/TrajectoryFile/TrajectoryFileReader.h"
#include "CacheEntry.h"
#include <mutex>
#include <thread>

struct LoadJob {
	int address;
};
/**
 *
 */
class JPSVISUE_API Cache
{
public:
	Cache(int bitsAssociativeness, int bitsIndex, int bitsWordOffset, std::string filePath);
	Cache();
	CacheEntry LoadCacheEntrySync(int address);
	void LoadCacheEntryAsync(int address);
	~Cache();
	const int GetFramesCount();
	void CheckToLoad();
	std::shared_ptr<TrajectoryFileReader> GetFileReader();
private:
	int GetPosition(int index, int tag);
	int ComputeStartAdress(int index, int tag);
	void LoadCacheLineAsync(int index, int tag);
	CacheLine LoadCacheLine(int index, int tag);
	int ComputeIndex(int address);
	int ComputeWordOffset(int address);
	int ComputeTag(int address);
	int m_bitsAssociativeness;
	int m_bitsIndex;
	int m_bitsWordOffset;
	int m_bitMaskIndex;
	int m_bitMaskWordOffset;
	int m_bitMaskTag;
	std::shared_ptr<TrajectoryFileReader> m_FileReader;
	unsigned int m_nextLRUid;
	void SetMasks();
	std::vector<std::vector<CacheLine>> m_cacheLines;
	std::vector<LoadJob> m_toLoadQueue;
	bool m_toLoadQueueHasLength;
	bool m_threadIsRunning;
};
