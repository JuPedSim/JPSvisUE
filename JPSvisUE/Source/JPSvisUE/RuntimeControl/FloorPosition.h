// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class JPSVISUE_API FloorPosition
{
public:
	FloorPosition();
	FloorPosition(int floorCount);
	~FloorPosition();
	void Increase();
	void Decrease();
	void SetPositionWithClamp(int pos);
	const int GetPosition();

private:
	int m_position;
	int m_floorCount;
	void SetUIinfo();
};
