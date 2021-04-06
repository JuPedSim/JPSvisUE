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
	m_trajectoryFilePath = "E:/Arbeit_Forschungszentrum/Repo/JPSvisUE/TestData/TestData.bin";
	m_cacheBitsAssociativeness = 0;
	m_cacheBitsIndex = 0;
	m_cacheBitsWordOffset = 0;
	m_isAutoPlay = false;
	m_timePerFrame = 0.018f;
	m_speedUpFactor = 1.0f;
	m_speedUpFactorIncrementSize = 0.25f;
	m_framePosition = FramePosition();
}

GlobalSettings* GlobalSettings::GetInstance()
{
	if (m_instance == NULL) {
		m_instance = new GlobalSettings();
	}
	return m_instance;
}

const float GlobalSettings::GetScalingFactor()
{
	return m_scalingFactor;
}
const float GlobalSettings::GetFloorThigness()
{
	return m_floorThigness;
}
const float GlobalSettings::GetWallBigHeight()
{
	return m_wallBigHeight;
}
const float GlobalSettings::GetWallSmallHeight()
{
	return m_wallSmallHeight;
}
const float GlobalSettings::GetViewObstractedCheckerDegree()
{
	return m_viewObstractedCheckerDegree;
}
const float GlobalSettings::GetAllowedObstractionDegree()
{
	return m_allowedObstractionDegree;
}
const ViewType GlobalSettings::GetViewType()
{
	return m_viewType;
}
const inline std::string GlobalSettings::GetTrajectoryFilePath()
{
	return m_trajectoryFilePath;
}
const inline int GlobalSettings::GetCacheBitsAssociativeness()
{
	return m_cacheBitsAssociativeness;
}
const inline int GlobalSettings::GetCacheBitsIndex()
{
	return m_cacheBitsIndex;
}
const inline int GlobalSettings::GetCacheBitsWordOffset()
{
	return m_cacheBitsWordOffset;
}
const inline bool GlobalSettings::GetIsAutoPlay()
{
	return m_isAutoPlay;
}
const inline float GlobalSettings::GetTimePerFrame()
{
	return m_timePerFrame;
}
const inline float GlobalSettings::GetSpeedUpFactor()
{
	return m_speedUpFactor;
}
inline const float GlobalSettings::GetSpeedUpFactorIncrementSize()
{
	return m_speedUpFactorIncrementSize;
}
inline FramePosition& GlobalSettings::GetFramePosition()
{
	return m_framePosition;
}
const float GlobalSettings::GetWallScaleChangeSpeed()
{
	return m_wallScaleChangeSpeed;
}
const inline float GlobalSettings::GetPedestrianHeight()
{
	return m_pedestrianHeight;
}
const inline float GlobalSettings::GetPedestrianWidth()
{
	return m_pedestrianWidth;
}
void GlobalSettings::SetViewType(ViewType vType)
{
	m_viewType = vType;
}

void GlobalSettings::SetIsAutoPlay(bool isAutoPlay)
{
	m_isAutoPlay = isAutoPlay;
}

void GlobalSettings::SetSpeedUpFactor(float speedUpFactor)
{
	m_speedUpFactor = speedUpFactor;
}

void GlobalSettings::SetFramePosition(FramePosition framePosition)
{
	m_framePosition = framePosition;
}
