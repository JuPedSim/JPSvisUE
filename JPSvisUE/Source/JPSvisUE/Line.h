// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class JPSVISUE_API Line
{
public:
	Line();
	Line(FVector p1,FVector p2);
	~Line();
private:
	FVector point1;
	FVector point2;
public:
	FVector GetPoint1();
	FVector GetPoint2();
};
