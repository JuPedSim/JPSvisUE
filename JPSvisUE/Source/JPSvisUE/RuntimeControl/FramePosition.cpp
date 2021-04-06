// Fill out your copyright notice in the Description page of Project Settings.


#include "FramePosition.h"

std::mutex positionMutex;

FramePosition::FramePosition()
{
	m_length = 0;
	m_frameTime = 0;
	m_position = 0;
	m_currentTime = 0;
	m_positionWasChanged = true;
}

FramePosition::FramePosition(int length, float frameTime)
{
	m_length = length;
	m_frameTime = frameTime;
	m_position = 0;
	m_currentTime = 0;
	m_positionWasChanged = true;
}

FramePosition::~FramePosition()
{
}

void FramePosition::TimeSensitiveChange(float delta)
{
	positionMutex.lock();
	m_currentTime += delta;
	float steps = m_currentTime / m_frameTime;
	if (steps >= 1.f || steps <= -1.f)
	{
		int addOn = std::floor(steps);
		int newPos = m_position + addOn;
		if (newPos >= m_length)
		{
			newPos = m_length - 1;
		}
		if (newPos < 0)
		{
			newPos = 0;
		}
		if (newPos!=m_position) 
		{
			m_positionWasChanged = true;
		}
		m_currentTime = m_currentTime - (float)addOn * m_frameTime;
		m_position = newPos;
	}
	positionMutex.unlock();
}

void FramePosition::Increase()
{
	positionMutex.lock();
	if (m_position<m_length-1) 
	{
		m_position++;
		m_positionWasChanged = true;
	}
	positionMutex.unlock();
}

void FramePosition::Decrease()
{
	positionMutex.lock();
	if (m_position > 0)
	{
		m_position--;
		m_positionWasChanged = true;
	}
	positionMutex.unlock();
}

inline const int FramePosition::GetPosition()
{
	return m_position;
}

inline bool FramePosition::GetPositionWasChanged()
{
	bool change = m_positionWasChanged;
	m_positionWasChanged = false;
	return change;
}
