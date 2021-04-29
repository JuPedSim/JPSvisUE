// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TrajectoryFileReader.h"
#include "CoreMinimal.h"

/**
 * 
 */
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
	int endPos;
};
struct TrajectoryFileFrameBoundaries
{
	int startPos;
	int stopPos;
};
struct BinaryTreeInformation
{
	int startPos;
	int stopPos;
	int startFrame;
	int stopFrame;
};
class JPSVISUE_API TrajectoryFileReaderTXT : public TrajectoryFileReader
{
public:
	TrajectoryFileReaderTXT();
	TrajectoryFileReaderTXT(std::string filePath);
	~TrajectoryFileReaderTXT();

	CacheLine LoadCacheLine(int startAddress, int count, int tag, unsigned int lruID) override;
private:
	TrajectoryFileFrameBoundaries m_boundaries;
	TrajectoryFileDataPositions m_positions;
	int m_lastPos;

	void SetFramesCount();
	void SetTimePerFrame();
	void SetFrameBoundaries();
	void SetTrajectoryFileDataPositions();

	TrajectoryFileFrameInfo GetFrameInfoWithoutStartEndPos(std::ifstream& is, long pos);
	TrajectoryFileFrameInfo GetFrameInfoWithStartEndPos(std::ifstream& is, TrajectoryFileFrameInfo frameInfo);

	std::vector<Person> ConvertFrameInfoToPersons(std::ifstream& is, TrajectoryFileFrameInfo frameInfo);

	std::vector<std::vector<Person>> Search(int frame, int count);
	TrajectoryFileFrameInfo SearchBinaryTree(std::ifstream& is, BinaryTreeInformation binaryTreeInformation, int searchedFrame);
	TrajectoryFileFrameInfo SearchHelper(std::ifstream& is, int frame);
	TrajectoryFileFrameInfo SearchForward(std::ifstream& is, int frame, TrajectoryFileFrameInfo startInfo);
	TrajectoryFileFrameInfo SearchBackward(std::ifstream& is, int frame, TrajectoryFileFrameInfo startInfo);
};
