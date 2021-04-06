// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <memory>
#include <vector>
#include "CoreMinimal.h"
#include <string>
#include "../RuntimeControl/FramePosition.h"
#include "../RuntimeControl/FloorPosition.h"


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
	float m_pedestrianHeight;
	float m_pedestrianWidth;
	int m_cacheBitsAssociativeness;
	int m_cacheBitsIndex;
	int m_cacheBitsWordOffset;
	std::string m_trajectoryFilePath;
	bool m_isAutoPlay;
	float m_timePerFrame;
	float m_wallScaleChangeSpeed;//fraction per second
	float m_speedUpFactor;
	float m_speedUpFactorIncrementSize;
	ViewType m_viewType;
	FramePosition m_framePosition;
	FloorPosition m_floorPosition;

public:
	//Getter
	inline const float GetScalingFactor();
	inline const float GetFloorThigness();
	inline const float GetWallBigHeight();
	inline const float GetWallSmallHeight();
	inline const float GetViewObstractedCheckerDegree();
	inline const float GetAllowedObstractionDegree();
	inline const float GetWallScaleChangeSpeed();
	inline const float GetPedestrianHeight();
	inline const float GetPedestrianWidth();
	inline const ViewType GetViewType();
	inline const std::string GetTrajectoryFilePath();
	inline const int GetCacheBitsAssociativeness();
	inline const int GetCacheBitsIndex();
	inline const int GetCacheBitsWordOffset();
	inline const bool GetIsAutoPlay();
	inline const float GetTimePerFrame();
	inline const float GetSpeedUpFactor();
	inline const float GetSpeedUpFactorIncrementSize();
	inline FramePosition& GetFramePosition();
	inline FloorPosition& GetFloorPosition();
	//Setter
	void SetViewType(ViewType viewType);
	void SetIsAutoPlay(bool isAutoPlay);
	void SetSpeedUpFactor(float speedUpFactor);
	void SetFramePosition(FramePosition framePosition);
	void SetFloorPosition(FloorPosition floorPosition);
};
