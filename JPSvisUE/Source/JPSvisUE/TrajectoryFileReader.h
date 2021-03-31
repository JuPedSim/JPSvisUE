// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CacheLine.h"
#include <string>
#include <fstream>

/**
 * 
 */
class JPSVISUE_API TrajectoryFileReader
{
public:
	TrajectoryFileReader();
	~TrajectoryFileReader();
	static CacheLine LoadCacheLine(int startAddress, int count, std::string filePath,int tag);
	static int GetFrames(std::string filePath);
};
