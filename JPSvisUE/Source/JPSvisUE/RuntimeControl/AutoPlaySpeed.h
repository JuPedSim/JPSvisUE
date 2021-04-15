// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 *
 */
class JPSVISUE_API AutoPlaySpeed
{
public:
	AutoPlaySpeed();
	~AutoPlaySpeed();
	void Increase();
	void Decrease();
	float GetSpeedUpFactor();
private:
	float m_speedUpFactor;
	void SetUIinfo();
};
