// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <JPSvisUE/CacheLine.cpp>
#include <string>

/**
 * 
 */
class JPSVISUE_API TrajectoryFileReader
{
public:
	TrajectoryFileReader();
	~TrajectoryFileReader();
	static CacheLine LoadCacheLine(int startAddress, int count, std::string filePath);
};
