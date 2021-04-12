// Fill out your copyright notice in the Description page of Project Settings.


#include "FramePosition.h"
#include "../Settings/GlobalSettings.h"
#include "../UI/UIwidget.h"

std::mutex positionMutex;

FramePosition::FramePosition()
{
	m_length = 1;
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
	SetUIinfo();
}

void FramePosition::Increase()
{
	positionMutex.lock();
	if (m_position<m_length-1) 
	{
		m_position++;
		m_positionWasChanged = true;
		SetUIinfo();
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
		SetUIinfo();
	}
	positionMutex.unlock();
}

void FramePosition::SetPositionWithClamp(int pos)
{
	positionMutex.lock();
	m_position = FMath::Clamp(pos,0,m_length-1);
	SetUIinfo();
	positionMutex.unlock();
}

void FramePosition::SetPositionWithFraction(float fraction)
{
	int pos = round(fraction*(float)(m_length-1));
	SetPositionWithClamp(pos);
}

const int FramePosition::GetPosition()
{
	return m_position;
}

bool FramePosition::GetPositionWasChanged()
{
	bool change = m_positionWasChanged;
	m_positionWasChanged = false;
	return change;
}

int FramePosition::GetLength()
{
	return m_length;
}

bool FramePosition::CheckPositionValid(int pos)
{
	if (pos>=0 && pos<m_length)
	{
		return true;
	}
	return false;
}

void FramePosition::SetUIinfo()
{
	float percent = (float)m_position / (float)(m_length-1);
	GlobalSettings* settings = GlobalSettings::GetInstance();
	std::stringstream ss;
	ss << (m_position + 1) << ":" << m_length;
	std::string str = ss.str();
	FString text(str.c_str());
	UUIwidget* ui = (UUIwidget*)settings->GetUI().get();
	if (ui!=nullptr) 
	{
		ui->m_frameTextBox->SetText(FText::FromString(text));
		ui->m_framePosSlider->SetValue(percent);
	}
}
