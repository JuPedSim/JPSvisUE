// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorDimensions.h"
#include "../../Settings/GlobalSettings.h"
#include <sstream>

FloorDimensions::FloorDimensions()
{
}

FloorDimensions::FloorDimensions(FVector minXminY, FVector minXmaxY, FVector maxXminY, FVector maxXmaxY)
{
	m_minXminY = minXminY;
	m_minXmaxY = minXmaxY;
	m_maxXminY = maxXminY;
	m_maxXmaxY = maxXmaxY;
}

FloorDimensions::~FloorDimensions()
{
	m_minXminY = FVector(0.f);
	m_minXmaxY = FVector(0.f);
	m_maxXminY = FVector(0.f);
	m_maxXmaxY = FVector(0.f);
}

FVector FloorDimensions::GetMinXminY()
{
	return m_minXminY;
}

FVector FloorDimensions::GetMinXmaxY()
{
	return m_minXmaxY;
}

FVector FloorDimensions::GetMaxXminY()
{
	return m_maxXminY;
}

FVector FloorDimensions::GetMaxXmaxY()
{
	return m_maxXmaxY;
}

bool FloorDimensions::checkCollision(FVector start, FVector v)
{
	FPlane plane = FPlane(m_minXminY, m_maxXminY, m_minXmaxY);

	if (abs(v.Z) < 0.00001f)
	{
		return false;
	}
	FVector intersection = FMath::LinePlaneIntersection(start, start + v, m_minXminY, FVector(0, 0, 1));
	float minX = m_minXminY.X;
	float maxX = m_maxXmaxY.X;
	float minY = m_minXminY.Y;
	float maxY = m_maxXmaxY.Y;
	float x = intersection.X;
	float y = intersection.Y;

	if (
		x >= minX &&
		x <= maxX &&
		y >= minY &&
		y <= maxY)
	{
		return true;
	}
	return false;
}
