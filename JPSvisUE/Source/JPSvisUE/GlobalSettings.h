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
	static GlobalSettings* m_instance;
	
	//Settings
	float m_scalingFactor;
	float m_floorThigness;
	float m_wallBigHeight;
	float m_wallSmallHeight;
	float m_viewObstractedCheckerDegree;
	float m_allowedObstractionDegree;
	//fraction per second
	float m_wallScaleChangeSpeed;
	ViewType m_viewType;

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
