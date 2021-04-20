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
struct TrajectoryFileDataPositions 
{
	int id;
	int x;
	int y;
	int z;
	int frame;
};
struct TrajectoryFileFrameInfo 
{
	int pos;
	int frame;
	int startPos;
};
struct TrajectoryFileFrameBoundaries
{
	int startPos;
	int stopPos;
};
/**
 *
 */
class JPSVISUE_API TrajectoryFileReader
{
public:
	TrajectoryFileReader();
	~TrajectoryFileReader();
	static CacheLine LoadCacheLine(int startAddress, int count, std::string filePath, int tag, unsigned int lruID);
	static int GetFrames(std::string filePath);
private:
	static CacheLine CacheLineConstructor(std::vector<CacheEntry> entries, int tag, unsigned int lruID);
	static std::vector<CacheEntry> LoadCacheLineBin(int startAddress, int count, std::string filePath);
	static std::vector<CacheEntry> LoadCacheLineTxt(int startAddress, int count, std::string filePath);
	static int GetFramesBin(std::string filePath);
	static int GetFramesTxt(std::string filePath);
	static TrajectoryFileFrameInfo GetFrameInfoWithoutStartPos(std::ifstream& is, long pos, long size, TrajectoryFileDataPositions trajectoryFileDataPositions, TrajectoryFileFrameBoundaries boundaries);
	static TrajectoryFileFrameInfo GetFrameInfoWithStartPos(std::ifstream& is, long size, TrajectoryFileFrameInfo frameInfo, TrajectoryFileDataPositions trajectoryFileDataPositions);


	static TrajectoryFileFrameBoundaries GetFrameBoundaries(std::ifstream& is, long size);

	static DataType GetDataType(std::string filePath);
};
