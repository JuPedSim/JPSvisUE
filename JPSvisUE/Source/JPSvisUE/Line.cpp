// Fill out your copyright notice in the Description page of Project Settings.


#include "Line.h"

Line::Line()
{
	m_point1 = FVector(0.f);
	m_point2 = FVector(0.f);
}

Line::Line(FVector p1, FVector p2)
{
	m_point1 = p1;
	m_point2 = p2;
}

Line::~Line()
{
}

FVector Line::GetPoint1()
{
	return m_point1;
}

FVector Line::GetPoint2()
{
	return m_point2;
}
