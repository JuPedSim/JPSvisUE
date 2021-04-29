// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <string>
#include <fstream>
#include <stdexcept>
#include <vector>
#include "../../Cache/CacheEntry.h"

class CacheLine;
enum DataType { BIN, TXT, NONE };
/**
 *
 */
class JPSVISUE_API TrajectoryFileReader
{
protected:
	TrajectoryFileReader();
	TrajectoryFileReader(std::string filePath);
	virtual ~TrajectoryFileReader();

public:
	virtual CacheLine LoadCacheLine(int startAddress, int count, int tag, unsigned int lruID) = 0;
	int GetFramesCount();
	double GetTimePerFrame();
	static std::shared_ptr<TrajectoryFileReader> CreateFileReader(std::string filePath);
protected:
	int m_framesCount;
	long m_fileSize;
	double m_timePerFrame;
	std::string m_filePath;

	//static CacheLine LoadCacheLine(int startAddress, int count, std::string filePath, int tag, unsigned int lruID);
//	static int GetFrames(std::string filePath);
//	static void SetFramerate(std::string filePath);
//private:
//	static CacheLine CacheLineConstructor(std::vector<CacheEntry> entries, int tag, unsigned int lruID);
//	static std::vector<CacheEntry> LoadCacheLineBin(int startAddress, int count, std::string filePath);
//	static std::vector<CacheEntry> LoadCacheLineTxt(int startAddress, int count, std::string filePath);
//	static int GetFramesBin(std::string filePath);
//	static int GetFramesTxt(std::string filePath);
//	static void SetFramerateBin(std::string filePath);
//	static void SetFramerateTxt(std::string filePath);
//	static TrajectoryFileFrameInfo GetFrameInfoWithoutStartEndPos(std::ifstream& is, long pos, long size, TrajectoryFileDataPositions trajectoryFileDataPositions);
//	static TrajectoryFileFrameInfo GetFrameInfoWithStartEndPos(std::ifstream& is, long size, TrajectoryFileFrameInfo frameInfo, TrajectoryFileDataPositions trajectoryFileDataPositions);
//	
//	static std::vector<Person> ConvertFrameInfoToPersons(std::ifstream& is, long size, TrajectoryFileFrameInfo frameInfo, TrajectoryFileDataPositions positions);
//
//	static std::vector<std::vector<Person>> Search(std::string filePath,int frame,int count);
//	static TrajectoryFileFrameInfo SearchBinaryTree(std::ifstream& is, BinaryTreeInformation binaryTreeInformation, int size, int searchedFrame, TrajectoryFileFrameBoundaries boundaries, TrajectoryFileDataPositions positions);
//	static TrajectoryFileFrameInfo SearchHelper(std::ifstream& is, int size, int frame, TrajectoryFileFrameBoundaries boundaries, TrajectoryFileDataPositions positions);
//	static TrajectoryFileFrameInfo SearchForward(std::ifstream& is, int frame, long size, TrajectoryFileFrameInfo startInfo, TrajectoryFileDataPositions trajectoryFileDataPositions, TrajectoryFileFrameBoundaries boundaries);
//	static TrajectoryFileFrameInfo SearchBackward(std::ifstream& is, int frame, long size, TrajectoryFileFrameInfo startInfo, TrajectoryFileDataPositions trajectoryFileDataPositions, TrajectoryFileFrameBoundaries boundaries);
//
//	static TrajectoryFileFrameBoundaries GetFrameBoundaries(std::ifstream& is, long size);
private:
	static DataType GetDataType(std::string filePath);
};
