// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalSettings.h"

GlobalSettings* GlobalSettings::m_instance = NULL;

GlobalSettings::GlobalSettings()
{
	m_scalingFactor = 10.0;
	m_floorThigness = 1.0;
	m_wallBigHeight = 10.0;
	m_wallSmallHeight = 1.0;
	m_viewObstractedCheckerDegree = 10;
	m_allowedObstractionDegree = 20;
	m_wallScaleChangeSpeed = 4;
	m_pedestrianHeight = 8;
	m_pedestrianWidth = 2;
	m_viewType = DYNAMIC_VIEW;
	m_trajectoryFilePath = "E:/Arbeit_Forschungszentrum/TestData10GB.bin";
	m_cacheBitsAssociativeness = 0;
	m_cacheBitsIndex = 0;
	m_cacheBitsWordOffset = 0;
	m_currentFrame = 0;
	m_framesCount = 1;
	m_isAutoPlay = false;
	m_timePerFrame = 0.001f;
}

GlobalSettings* GlobalSettings::GetInstance()
{
	if (m_instance == NULL) {
		m_instance = new GlobalSettings();
	}
	return m_instance;
}

float GlobalSettings::GetScalingFactor()
{
	return m_scalingFactor;
}
float GlobalSettings::GetFloorThigness()
{
	return m_floorThigness;
}
float GlobalSettings::GetWallBigHeight()
{
	return m_wallBigHeight;
}
float GlobalSettings::GetWallSmallHeight()
{
	return m_wallSmallHeight;
}
float GlobalSettings::GetViewObstractedCheckerDegree()
{
	return m_viewObstractedCheckerDegree;
}
float GlobalSettings::GetAllowedObstractionDegree()
{
	return m_allowedObstractionDegree;
}
ViewType GlobalSettings::GetViewType()
{
	return m_viewType;
}
inline std::string GlobalSettings::GetTrajectoryFilePath()
{
	return m_trajectoryFilePath;
}
inline int GlobalSettings::GetCacheBitsAssociativeness()
{
	return m_cacheBitsAssociativeness;
}
inline int GlobalSettings::GetCacheBitsIndex()
{
	return m_cacheBitsIndex;
}
inline int GlobalSettings::GetCacheBitsWordOffset()
{
	return m_cacheBitsWordOffset;
}
inline int GlobalSettings::GetFramesCount()
{
	return m_framesCount;
}
inline int GlobalSettings::GetCurrentFrame()
{
	return m_currentFrame;
}
inline bool GlobalSettings::GetIsAutoPlay()
{
	return m_isAutoPlay;
}
inline float GlobalSettings::GetTimePerFrame()
{
	return m_timePerFrame;
}
float GlobalSettings::GetWallScaleChangeSpeed()
{
	return m_wallScaleChangeSpeed;
}
inline float GlobalSettings::GetPedestrianHeight()
{
	return m_pedestrianHeight;
}
inline float GlobalSettings::GetPedestrianWidth()
{
	return m_pedestrianWidth;
}
void GlobalSettings::SetViewType(ViewType vType)
{
	m_viewType = vType;
}

void GlobalSettings::SetFramesCount(int framesCount)
{
	m_framesCount = framesCount;
}

void GlobalSettings::SetCurrentFrame(int currentFrame)
{
	m_currentFrame = currentFrame;
}

void GlobalSettings::SetIsAutoPlay(bool isAutoPlay)
{
	m_isAutoPlay = isAutoPlay;
}
