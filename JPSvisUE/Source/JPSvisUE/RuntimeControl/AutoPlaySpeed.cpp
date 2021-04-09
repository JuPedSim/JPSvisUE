// Fill out your copyright notice in the Description page of Project Settings.


#include "AutoPlaySpeed.h"

AutoPlaySpeed::AutoPlaySpeed()
{
	m_speedUpFactor = 1.0f;
}

AutoPlaySpeed::~AutoPlaySpeed()
{
}

void AutoPlaySpeed::Increase()
{
	GlobalSettings* settings = GlobalSettings::GetInstance();
	m_speedUpFactor +=settings->GetSpeedUpFactorIncrementSize();
	SetUIinfo();
}

void AutoPlaySpeed::Decrease()
{
	GlobalSettings* settings = GlobalSettings::GetInstance();
	m_speedUpFactor -=settings->GetSpeedUpFactorIncrementSize();
	SetUIinfo();
}

float AutoPlaySpeed::GetSpeedUpFactor()
{
	return m_speedUpFactor;
}

void AutoPlaySpeed::SetUIinfo()
{
	GlobalSettings* settings = GlobalSettings::GetInstance();
	std::stringstream ss;
	ss << "speed Factor: " << m_speedUpFactor;
	std::string str = ss.str();
	FString text(str.c_str());
	UUIwidget* ui = (UUIwidget*)settings->GetUI();
	if (ui != nullptr)
	{
		ui->m_speedTextBlock->SetText(FText::FromString(text));
	}
}
