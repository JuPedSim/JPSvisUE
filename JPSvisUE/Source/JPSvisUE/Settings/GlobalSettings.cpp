// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalSettings.h"
#include "../RuntimeControl/FramePosition.h"
#include "../RuntimeControl/FloorPosition.h"
#include "../RuntimeControl/AutoPlaySpeed.h"
#include "../UI/UIwidget.h"

GlobalSettings* GlobalSettings::m_instance = nullptr;
std::once_flag GlobalSettings::initInstanceFlag;

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
	m_wallViewType = WallViewType::DYNAMIC_VIEW;
	m_floorViewType = FloorViewType::ALL_BELOW_VIEW;
	m_trajectoryFilePath = "";
	m_trajectoryFileChanged = false;
	m_structureFilePath = "";
	m_structureFileChanged = false;
	m_cacheBitsAssociativeness = 0;// 8;
	m_cacheBitsIndex = 0;
	m_cacheBitsWordOffset = 0;// 4;
	m_preFetchCacheForward = 100;
	m_preFetchCacheBackward = 100;
	m_isAutoPlay = false;
	m_timePerFrame = 1.f;
	m_speedUpFactorIncrementSize = 0.25f;
	m_framePosition = std::make_shared<FramePosition>();
	m_floorPosition = std::make_shared<FloorPosition>();
	m_autoPlaySpeed = std::make_shared<AutoPlaySpeed>();
	m_cameraSpringArmLengthMax = 1000.f;
	m_cameraSpringArmLengthMin = 0.f;
	m_zoomSpeed = 3.f;
	m_movementSpeed = 4.f;
	m_yawSpeed = 1.f;
	m_pitchSpeed = 1.f;
	m_floorHeights = std::vector<float>();
	m_floorHeights.resize(1);
	m_floorHeights.at(0) = 0;
	m_camOffsetFromFloor = 2;
	m_ui = nullptr;
	m_lastFileReaderPos = 0;
	/*
		At 88195 frames with 297 Pedestrians each:

		57.43 seconds to Load from beginning to end (without binary Tree)
		1407.77 seconds to Load from end to beginning (without binary Tree)
	
		forward: 0.00000219 seconds per Pedestrian
		backward: 0.00005374 seconds per Pedestrian
		
		forward is 24.51 times faster than backwards

	*/
	m_txtReaderForwardThreshhold =  2;
	m_txtReaderBackwardThreshhold = (int)round((float)m_txtReaderForwardThreshhold/24.51);// 3;
	m_txtReaderBinaryTreeMinimumGap = 1000;
}

void GlobalSettings::InitSingleton()
{
	m_instance = new GlobalSettings();
}

GlobalSettings* GlobalSettings::GetInstance()
{
	std::call_once(initInstanceFlag, &GlobalSettings::InitSingleton);
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
const WallViewType GlobalSettings::GetWallViewType()
{
	return m_wallViewType;
}
const FloorViewType GlobalSettings::GetFloorViewType()
{
	return m_floorViewType;
}
const std::string GlobalSettings::GetTrajectoryFilePath()
{
	return m_trajectoryFilePath;
}
const std::string GlobalSettings::GetStructureFilePath()
{
	return m_structureFilePath;
}
const int GlobalSettings::GetCacheBitsAssociativeness()
{
	return m_cacheBitsAssociativeness;
}
const int GlobalSettings::GetCacheBitsIndex()
{
	return m_cacheBitsIndex;
}
const int GlobalSettings::GetCacheBitsWordOffset()
{
	return m_cacheBitsWordOffset;
}
const int GlobalSettings::GetPreFetchCacheForward()
{
	return m_preFetchCacheForward;
}
const int GlobalSettings::GetPreFetchCacheBackward()
{
	return m_preFetchCacheBackward;
}
const bool GlobalSettings::GetIsAutoPlay()
{
	return m_isAutoPlay;
}
const float GlobalSettings::GetTimePerFrame()
{
	return m_timePerFrame;
}
const float GlobalSettings::GetSpeedUpFactorIncrementSize()
{
	return m_speedUpFactorIncrementSize;
}
std::shared_ptr<FramePosition> GlobalSettings::GetFramePosition()
{
	return m_framePosition;
}
std::shared_ptr<FloorPosition> GlobalSettings::GetFloorPosition()
{
	return m_floorPosition;
}
std::shared_ptr<AutoPlaySpeed> GlobalSettings::GetAutoPlaySpeed()
{
	return m_autoPlaySpeed;
}
const float GlobalSettings::GetCameraSpringArmLengthMax()
{
	return m_cameraSpringArmLengthMax;
}
const float GlobalSettings::GetCameraSpringArmLengthMin()
{
	return m_cameraSpringArmLengthMin;
}
const float GlobalSettings::GetZoomSpeed()
{
	return m_zoomSpeed;
}
const float GlobalSettings::GetMovementSpeed()
{
	return m_movementSpeed;
}
const float GlobalSettings::GetYawSpeed()
{
	return m_yawSpeed;
}
const float GlobalSettings::GetPitchSpeed()
{
	return m_pitchSpeed;
}
const std::vector<float>& GlobalSettings::GetFloorHeights()
{
	return m_floorHeights;
}
const float GlobalSettings::GetCamOffsetFromFloor()
{
	return m_camOffsetFromFloor;
}
const bool GlobalSettings::GetTrajectoryFileChanged()
{
	bool value = m_trajectoryFileChanged;
	if (m_trajectoryFileChanged)
	{
		m_trajectoryFileChanged = false;
	}
	return value;
}
const bool GlobalSettings::GetStructureFileChanged()
{
	bool value = m_structureFileChanged;
	if (m_structureFileChanged)
	{
		m_structureFileChanged = false;
	}
	return value;
}
std::shared_ptr<UUserWidget> GlobalSettings::GetUI()
{
	return m_ui;
}
const int GlobalSettings::GetLastFileReaderPos()
{
	return m_lastFileReaderPos;
}
const int GlobalSettings::GetTxtReaderForwardThreshhold()
{
	return m_txtReaderForwardThreshhold;
}
const int GlobalSettings::GetTxtReaderBackwardThreshhold()
{
	return m_txtReaderBackwardThreshhold;
}
const int GlobalSettings::GetTxtReaderBinaryTreeMinimumGap()
{
	return m_txtReaderBinaryTreeMinimumGap;
}
const float GlobalSettings::GetWallScaleChangeSpeed()
{
	return m_wallScaleChangeSpeed;
}
const float GlobalSettings::GetPedestrianHeight()
{
	return m_pedestrianHeight;
}
const float GlobalSettings::GetPedestrianWidth()
{
	return m_pedestrianWidth;
}
void GlobalSettings::SetWallViewType(WallViewType wallViewType)
{
	m_wallViewType = wallViewType;
}

void GlobalSettings::SetFloorViewType(FloorViewType floorViewType)
{
	m_floorViewType = floorViewType;
}

void GlobalSettings::SetIsAutoPlay(bool isAutoPlay)
{
	m_isAutoPlay = isAutoPlay;
}

void GlobalSettings::SetFramePosition(std::shared_ptr<FramePosition> framePosition)
{
	m_framePosition = framePosition;
}

void GlobalSettings::SetFloorPosition(std::shared_ptr<FloorPosition> floorPosition)
{
	m_floorPosition = floorPosition;
}

void GlobalSettings::SetFloorHeights(std::vector<float>& floorHeights)
{
	m_floorHeights = floorHeights;
}

void GlobalSettings::SetTrajectoryFilePath(std::string path)
{
	m_trajectoryFilePath = path;
	m_trajectoryFileChanged = true;
}
void GlobalSettings::SetStructureFilePath(std::string path)
{
	m_structureFilePath = path;
	m_structureFileChanged = true;
}

void GlobalSettings::SetUI(std::shared_ptr<UUserWidget> ui)
{
	m_ui = ui;
}

void GlobalSettings::SetLastFileReaderPos(int pos)
{
	m_lastFileReaderPos = pos;
}

void GlobalSettings::SetTimePerFrame(float time)
{
	m_timePerFrame = time;
}
