// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

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
private:
	FVector minXminY;
	FVector minXmaxY;
	FVector maxXminY;
	FVector maxXmaxY;
};
