// Fill out your copyright notice in the Description page of Project Settings.


#include "Line.h"

Line::Line()
{
	point1 = FVector(0.f);
	point2 = FVector(0.f);
}

Line::Line(FVector p1, FVector p2)
{
	point1 = p1;
	point2 = p2;
}

Line::~Line()
{
}

FVector Line::GetPoint1()
{
	return point1;
}

FVector Line::GetPoint2()
{
	return point2;
}
