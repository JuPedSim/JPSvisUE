// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorDimensions.h"

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
