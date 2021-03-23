// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorDimensions.h"
#include <sstream>

FloorDimensions::FloorDimensions()
{
}

FloorDimensions::FloorDimensions(FVector minXminY, FVector minXmaxY, FVector maxXminY, FVector maxXmaxY)
{
	this->minXminY = minXminY;
	this->minXmaxY = minXmaxY;
	this->maxXminY = maxXminY;
	this->maxXmaxY = maxXmaxY;
}

FloorDimensions::~FloorDimensions()
{
	this->minXminY = FVector(0.f);
	this->minXmaxY = FVector(0.f);
	this->maxXminY = FVector(0.f);
	this->maxXmaxY = FVector(0.f);
}

FVector FloorDimensions::GetMinXminY()
{
	return this->minXminY;
}

FVector FloorDimensions::GetMinXmaxY()
{
	return this->minXmaxY;
}

FVector FloorDimensions::GetMaxXminY()
{
	return this->maxXminY;
}

FVector FloorDimensions::GetMaxXmaxY()
{
	return this->maxXmaxY;
}

bool FloorDimensions::checkCollision(FVector start, FVector v)
{
	FPlane plane = FPlane(this->minXminY, this->maxXminY, this->minXmaxY);

	if (abs(v.Z) < 0.00001f)
	{
		return false;
	}
	FVector intersection = FMath::LinePlaneIntersection(start, start + v, this->minXminY, FVector(0, 0, 1));
	float minX = this->minXminY.X;
	float maxX = this->maxXmaxY.X;
	float minY = this->minXminY.Y;
	float maxY = this->maxXmaxY.Y;
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
