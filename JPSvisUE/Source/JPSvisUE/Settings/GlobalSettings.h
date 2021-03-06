// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <memory>
#include <vector>
#include "CoreMinimal.h"
#include <string>
#include <mutex>
#include <thread>




enum WallViewType { LARGE_VIEW, SMALL_VIEW, DYNAMIC_VIEW };
enum FloorViewType { ALL_VIEW, ALL_BELOW_VIEW, ONLY_VIEW };

class FramePosition;
class FloorPosition;
class AutoPlaySpeed;
class UUIwidget;

/**
 *
 */
class JPSVISUE_API GlobalSettings
{
public:
	static GlobalSettings* GetInstance();
private:
	GlobalSettings();
	static GlobalSettings* m_instance;
	static void InitSingleton();
	static std::once_flag initInstanceFlag;

	//Settings
	//Visualisation factors
	float m_scalingFactor;
	float m_floorThigness;
	float m_wallBigHeight;
	float m_wallSmallHeight;
	//dynamic wall settings
	float m_viewObstractedCheckerDegree;
	float m_allowedObstractionDegree;
	//pedestrian settings
	float m_pedestrianHeight;
	float m_pedestrianWidth;
	//cache settings
	int m_cacheBitsAssociativeness;
	int m_cacheBitsIndex;
	int m_cacheBitsWordOffset;
	int m_preFetchCacheForward;
	int m_preFetchCacheBackward;
	//File information
	std::string m_trajectoryFilePath;
	bool m_trajectoryFileChanged;
	std::string m_structureFilePath;
	bool m_structureFileChanged;
	//auto play values
	bool m_isAutoPlay;
	float m_timePerFrame;
	float m_speedUpFactorIncrementSize;
	//runtime Values
	std::shared_ptr<FramePosition> m_framePosition;
	std::shared_ptr<FloorPosition> m_floorPosition;
	std::shared_ptr<AutoPlaySpeed> m_autoPlaySpeed;
	//transition speed from for example small to big
	float m_wallScaleChangeSpeed;//fraction per second
	//view types
	WallViewType m_wallViewType;
	FloorViewType m_floorViewType;
	//camera settings
	float m_cameraSpringArmLengthMax;
	float m_cameraSpringArmLengthMin;
	float m_zoomSpeed;
	float m_movementSpeed;
	float m_yawSpeed;
	float m_pitchSpeed;
	float m_camOffsetFromFloor;
	//structure floor heights
	std::vector<float> m_floorHeights;
	//ui pointer
	std::shared_ptr<UUserWidget> m_ui;
	//txt trajectory file loader settings
	int m_txtReaderForwardThreshhold;
	int m_txtReaderBackwardThreshhold;
	int m_txtReaderBinaryTreeMinimumGap;
	//animation
	float m_animationChangePerUnitTraveled;
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
	const std::string GetStructureFilePath();
	const int GetCacheBitsAssociativeness();
	const int GetCacheBitsIndex();
	const int GetCacheBitsWordOffset();
	const int GetPreFetchCacheForward();
	const int GetPreFetchCacheBackward();
	const bool GetIsAutoPlay();
	const float GetTimePerFrame();
	const float GetSpeedUpFactorIncrementSize();
	std::shared_ptr<FramePosition> GetFramePosition();
	std::shared_ptr<FloorPosition> GetFloorPosition();
	std::shared_ptr<AutoPlaySpeed> GetAutoPlaySpeed();
	const float GetCameraSpringArmLengthMax();
	const float GetCameraSpringArmLengthMin();
	const float GetZoomSpeed();
	const float GetMovementSpeed();
	const float GetYawSpeed();
	const float GetPitchSpeed();
	const std::vector<float>& GetFloorHeights();
	const float GetCamOffsetFromFloor();
	const bool GetTrajectoryFileChanged();
	const bool GetStructureFileChanged();
	std::shared_ptr<UUserWidget> GetUI();
	const int GetTxtReaderForwardThreshhold();
	const int GetTxtReaderBackwardThreshhold();
	const int GetTxtReaderBinaryTreeMinimumGap();
	const float GetAnimationChangePerUnitTraveled();

	//Setter
	void SetWallViewType(WallViewType wallViewType);
	void SetFloorViewType(FloorViewType floorViewType);
	void SetIsAutoPlay(bool isAutoPlay);
	void SetFramePosition(std::shared_ptr<FramePosition> framePosition);
	void SetFloorPosition(std::shared_ptr<FloorPosition> floorPosition);
	void SetFloorHeights(std::vector<float>& floorHeights);
	void SetTrajectoryFilePath(std::string path);
	void SetStructureFilePath(std::string path);
	void SetUI(std::shared_ptr<UUserWidget> ui);
	void SetTimePerFrame(float time);
};
