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
	float m_pedestrianHeight;
	float m_pedestrianWidth;
	int m_cacheBitsAssociativeness;
	int m_cacheBitsIndex;
	int m_cacheBitsWordOffset;
	std::string m_trajectoryFilePath;
	int m_framesCount;
	int m_currentFrame;
	bool m_isAutoPlay;
	float m_timePerFrame;
	float m_wallScaleChangeSpeed;//fraction per second
	float m_speedUpFactor;
	float m_speedUpFactorIncrementSize;
	ViewType m_viewType;

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
	inline const int GetFramesCount();
	inline const int GetCurrentFrame();
	inline const bool GetIsAutoPlay();
	inline const float GetTimePerFrame();
	inline const float GetSpeedUpFactor();
	inline const float GetSpeedUpFactorIncrementSize();
	//Setter
	void SetViewType(ViewType viewType);
	void SetFramesCount(int framesCount);
	void SetCurrentFrame(int currentFrame);
	void SetIsAutoPlay(bool isAutoPlay);
	void SetSpeedUpFactor(float speedUpFactor);
};
