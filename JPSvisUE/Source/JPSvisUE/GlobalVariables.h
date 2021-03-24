// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
static const float scalingFactor = 10.0;
static const float floorThigness = 1.0;
static const float wallBigHeight = 10.0;
static const float wallSmallHeight = 1.0;
static const float zeroVal = 0.001f;
static const float viewObstractedCheckerDegree = 10;
static const float allowedObstractionDegree = 20;
class JPSVISUE_API GlobalVariables
{
public:
	GlobalVariables();
	~GlobalVariables();
};
