// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TrajectoryFileReader.h"
#include "CoreMinimal.h"

/**
 * 
 */
class CacheLine;
class JPSVISUE_API TrajectoryFileReaderBIN : public TrajectoryFileReader
{
public:
	TrajectoryFileReaderBIN();
	TrajectoryFileReaderBIN(std::string filePath);
	~TrajectoryFileReaderBIN();

	CacheLine LoadCacheLine(int startAddress, int count, int tag, unsigned int lruID) override;
private:
	void SetFramesCount();
	void SetTimePerFrame();
};
