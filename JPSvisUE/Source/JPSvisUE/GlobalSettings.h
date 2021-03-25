// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

enum ViewType { LARGE_VIEW, SMALL_VIEW, DYNAMIC_VIEW };

class JPSVISUE_API GlobalSettings
{
public:
	static GlobalSettings* GetInstance();
private:
	GlobalSettings();
	static GlobalSettings* instance;
	
	//Settings
	float scalingFactor;
	float floorThigness;
	float wallBigHeight;
	float wallSmallHeight;
	float viewObstractedCheckerDegree;
	float allowedObstractionDegree;
	//fraction per second
	float wallScaleChangeSpeed; 
	ViewType viewType;

public:
	//Getter
	inline float GetScalingFactor();
	inline float GetFloorThigness();
	inline float GetWallBigHeight();
	inline float GetWallSmallHeight();
	inline float GetViewObstractedCheckerDegree();
	inline float GetAllowedObstractionDegree();
	inline float GetWallScaleChangeSpeed();
	inline ViewType GetViewType();
	//Setter
	void SetViewType(ViewType viewType);
};
