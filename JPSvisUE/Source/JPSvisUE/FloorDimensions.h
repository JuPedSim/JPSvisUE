// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GlobalSettings.h"
/**
 * 
 */
class JPSVISUE_API FloorDimensions
{
public:
	FloorDimensions();
	FloorDimensions(FVector minXminY,FVector minXmaxY,FVector maxXminY,FVector maxXmaxY);
	~FloorDimensions();
	FVector GetMinXminY();
	FVector GetMinXmaxY();
	FVector GetMaxXminY();
	FVector GetMaxXmaxY();
	bool checkCollision(FVector start,FVector v);
private:
	FVector m_minXminY;
	FVector m_minXmaxY;
	FVector m_maxXminY;
	FVector m_maxXmaxY;
};
