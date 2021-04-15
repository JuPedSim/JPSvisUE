// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <string>
#include <fstream>
#include <stdexcept>
#include <vector>

class CacheLine;
class CacheEntry;
enum DataType { BIN, TXT, NONE };
/**
 * 
 */
class JPSVISUE_API TrajectoryFileReader
{
public:
	TrajectoryFileReader();
	~TrajectoryFileReader();
	static CacheLine LoadCacheLine(int startAddress, int count, std::string filePath,int tag, unsigned int lruID);
	static int GetFrames(std::string filePath);
private:
	static CacheLine CacheLineConstractor(std::vector<CacheEntry> entries,int tag, unsigned int lruID);
	static std::vector<CacheEntry> LoadCacheLineBin(int startAddress, int count, std::string filePath);
	static std::vector<CacheEntry> LoadCacheLineTxt(int startAddress, int count, std::string filePath);
	static int GetFramesBin(std::string filePath);
	static int GetFramesTxt(std::string filePath);
	static DataType GetDataType(std::string filePath);
};
