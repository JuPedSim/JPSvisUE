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
	inline float GetPedestrianHeight();
	inline float GetPedestrianWidth();
	inline ViewType GetViewType();
	inline std::string GetTrajectoryFilePath();
	inline int GetCacheBitsAssociativeness();
	inline int GetCacheBitsIndex();
	inline int GetCacheBitsWordOffset();
	inline int GetFramesCount();
	inline int GetCurrentFrame();
	inline bool GetIsAutoPlay();
	inline float GetTimePerFrame();
	//Setter
	void SetViewType(ViewType viewType);
	void SetFramesCount(int framesCount);
	void SetCurrentFrame(int currentFrame);
	void SetIsAutoPlay(bool isAutoPlay);
};
