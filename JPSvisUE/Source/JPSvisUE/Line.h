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
	FVector m_point1;
	FVector m_point2;
public:
	const FVector GetPoint1();
	const FVector GetPoint2();
};
