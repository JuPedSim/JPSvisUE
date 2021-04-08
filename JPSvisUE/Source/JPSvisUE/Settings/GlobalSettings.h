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

enum WallViewType { LARGE_VIEW, SMALL_VIEW, DYNAMIC_VIEW };
enum FloorViewType { ALL_VIEW, ALL_BELOW_VIEW, ONLY_VIEW};

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
	bool m_trajectoryFileChanged;
	bool m_isAutoPlay;
	float m_timePerFrame;
	float m_wallScaleChangeSpeed;//fraction per second
	float m_speedUpFactor;
	float m_speedUpFactorIncrementSize;
	WallViewType m_wallViewType;
	FloorViewType m_floorViewType;
	FramePosition m_framePosition;
	FloorPosition m_floorPosition;
	float m_cameraSpringArmLengthMax;
	float m_cameraSpringArmLengthMin;
	float m_zoomSpeed;
	float m_movementSpeed;
	float m_yawSpeed;
	float m_pitchSpeed;
	std::vector<float> m_floorHeights;
	float m_camOffsetFromFloor;

public:
	//Getter
	const float GetScalingFactor();
	const float GetFloorThigness();
	const float GetWallBigHeight();
	const float GetWallSmallHeight();
	const float GetViewObstractedCheckerDegree();
	const float GetAllowedObstractionDegree();
	const float GetWallScaleChangeSpeed();
	const float GetPedestrianHeight();
	const float GetPedestrianWidth();
	const WallViewType GetWallViewType();
	const FloorViewType GetFloorViewType();
	const std::string GetTrajectoryFilePath();
	const int GetCacheBitsAssociativeness();
	const int GetCacheBitsIndex();
	const int GetCacheBitsWordOffset();
	const bool GetIsAutoPlay();
	const float GetTimePerFrame();
	const float GetSpeedUpFactor();
	const float GetSpeedUpFactorIncrementSize();
	FramePosition& GetFramePosition();
	FloorPosition& GetFloorPosition();
	const float GetCameraSpringArmLengthMax();
	const float GetCameraSpringArmLengthMin();
	const float GetZoomSpeed();
	const float GetMovementSpeed();
	const float GetYawSpeed();
	const float GetPitchSpeed();
	const std::vector<float>& GetFloorHeights();
	const float GetCamOffsetFromFloor();
	const bool GetTrajectoryFileChanged();
	//Setter
	void SetWallViewType(WallViewType wallViewType);
	void SetFloorViewType(FloorViewType floorViewType);
	void SetIsAutoPlay(bool isAutoPlay);
	void SetSpeedUpFactor(float speedUpFactor);
	void SetFramePosition(FramePosition framePosition);
	void SetFloorPosition(FloorPosition floorPosition);
	void SetFloorHeights(std::vector<float>& floorHeights);
	void SetTrajectoryFilePath(std::string path);
	void SetTrajectoryFileWasChanged();
};
