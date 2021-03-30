// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <memory>
#include <vector>
#include "CoreMinimal.h"
#include <string>

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
	int m_cacheBitsAssociativeness;
	int m_cacheBitsIndex;
	int m_cacheBitsWordOffset;
	std::string m_trajectoryFilePath;
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
	inline std::string GetTrajectoryFilePath();
	inline int GetCacheBitsAssociativeness();
	inline int GetCacheBitsIndex();
	inline int GetCacheBitsWordOffset();
	//Setter
	void SetViewType(ViewType viewType);
};
