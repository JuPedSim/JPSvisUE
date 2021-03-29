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
	m_viewType = DYNAMIC_VIEW;
}

GlobalSettings* GlobalSettings::GetInstance()
{
	if (m_instance == NULL) {
		m_instance = new GlobalSettings();
	}
	return m_instance;
}

float GlobalSettings::GetScalingFactor()
{
	return m_scalingFactor;
}
float GlobalSettings::GetFloorThigness()
{
	return m_floorThigness;
}
float GlobalSettings::GetWallBigHeight()
{
	return m_wallBigHeight;
}
float GlobalSettings::GetWallSmallHeight()
{
	return m_wallSmallHeight;
}
float GlobalSettings::GetViewObstractedCheckerDegree()
{
	return m_viewObstractedCheckerDegree;
}
float GlobalSettings::GetAllowedObstractionDegree()
{
	return m_allowedObstractionDegree;
}
ViewType GlobalSettings::GetViewType()
{
	return m_viewType;
}
float GlobalSettings::GetWallScaleChangeSpeed()
{
	return m_wallScaleChangeSpeed;
}
void GlobalSettings::SetViewType(ViewType vType)
{
	m_viewType = vType;
}
