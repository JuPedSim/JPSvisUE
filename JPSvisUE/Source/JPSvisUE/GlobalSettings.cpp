// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalSettings.h"

GlobalSettings* GlobalSettings::instance = NULL;

GlobalSettings::GlobalSettings()
{
	this->scalingFactor = 10.0;
	this->floorThigness = 1.0;
	this->wallBigHeight = 10.0;
	this->wallSmallHeight = 1.0;
	this->viewObstractedCheckerDegree = 10;
	this->allowedObstractionDegree = 20;
	this->wallScaleChangeSpeed = 4;
	this->viewType = DYNAMIC_VIEW;
}

GlobalSettings* GlobalSettings::GetInstance()
{
	if (instance == NULL) {
		instance = new GlobalSettings();
	}
	return instance;
}

float GlobalSettings::GetScalingFactor()
{
	return this->scalingFactor;
}
float GlobalSettings::GetFloorThigness()
{
	return this->floorThigness;
}
float GlobalSettings::GetWallBigHeight()
{
	return this->wallBigHeight;
}
float GlobalSettings::GetWallSmallHeight()
{
	return this->wallSmallHeight;
}
float GlobalSettings::GetViewObstractedCheckerDegree()
{
	return this->viewObstractedCheckerDegree;
}
float GlobalSettings::GetAllowedObstractionDegree()
{
	return this->allowedObstractionDegree;
}
ViewType GlobalSettings::GetViewType()
{
	return this->viewType;
}
float GlobalSettings::GetWallScaleChangeSpeed()
{
	return this->wallScaleChangeSpeed;
}
void GlobalSettings::SetViewType(ViewType vType)
{
	this->viewType = vType;
}