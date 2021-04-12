// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <cmath>
#include "CoreMinimal.h"

#include <mutex>
/**
 * 
 */
class JPSVISUE_API FramePosition
{
public:
	FramePosition();
	FramePosition(int length, float frameTime);
	~FramePosition();
	void TimeSensitiveChange(float delta);
	void Increase();
	void Decrease();
	void SetPositionWithClamp(int pos);
	void SetPositionWithFraction(float fraction);
	const int GetPosition();
	bool GetPositionWasChanged();
	int GetLength();
private:
	int m_position;
	int m_length;
	float m_frameTime;
	float m_currentTime;
	bool m_positionWasChanged;
	void SetUIinfo();
};
