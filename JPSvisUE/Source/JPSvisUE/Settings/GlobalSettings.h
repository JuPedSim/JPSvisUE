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
	inline const float GetScalingFactor();
	inline const float GetFloorThigness();
	inline const float GetWallBigHeight();
	inline const float GetWallSmallHeight();
	inline const float GetViewObstractedCheckerDegree();
	inline const float GetAllowedObstractionDegree();
	inline const float GetWallScaleChangeSpeed();
	inline const float GetPedestrianHeight();
	inline const float GetPedestrianWidth();
	inline const WallViewType GetWallViewType();
	inline const FloorViewType GetFloorViewType();
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
	inline const float GetCameraSpringArmLengthMax();
	inline const float GetCameraSpringArmLengthMin();
	inline const float GetZoomSpeed();
	inline const float GetMovementSpeed();
	inline const float GetYawSpeed();
	inline const float GetPitchSpeed();
	inline const std::vector<float>& GetFloorHeights();
	inline const float GetCamOffsetFromFloor();
	//Setter
	void SetWallViewType(WallViewType wallViewType);
	void SetFloorViewType(FloorViewType floorViewType);
	void SetIsAutoPlay(bool isAutoPlay);
	void SetSpeedUpFactor(float speedUpFactor);
	void SetFramePosition(FramePosition framePosition);
	void SetFloorPosition(FloorPosition floorPosition);
	void SetFloorHeights(std::vector<float>& floorHeights);
};
