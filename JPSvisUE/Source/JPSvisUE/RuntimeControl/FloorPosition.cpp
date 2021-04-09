// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorPosition.h"

FloorPosition::FloorPosition()
{
	m_position = 0;
	m_floorCount = 1;
}

FloorPosition::FloorPosition(int floorCount)
{
	m_position = 0;
	m_floorCount = floorCount;
}

FloorPosition::~FloorPosition()
{
}

void FloorPosition::Increase()
{
	if (m_position < m_floorCount - 1)
	{
		m_position++;
		SetUIinfo();
	}
}

void FloorPosition::Decrease()
{
	if (m_position > 0)
	{
		m_position--;
		SetUIinfo();
	}
}

void FloorPosition::SetPositionWithClamp(int pos)
{
	m_position = FMath::Clamp(pos, 0, m_floorCount - 1);
	SetUIinfo();
}

const int FloorPosition::GetPosition()
{
	return m_position;
}

void FloorPosition::SetUIinfo()
{
	GlobalSettings* settings = GlobalSettings::GetInstance();
	std::stringstream ss;
	ss << (m_position + 1) << ". Floor";
	std::string str = ss.str();
	FString text(str.c_str());
	UUIwidget* ui = (UUIwidget*)settings->GetUI();
	if (ui != nullptr)
	{
		ui->m_floorTextBlock->SetText(FText::FromString(text));
	}
}
