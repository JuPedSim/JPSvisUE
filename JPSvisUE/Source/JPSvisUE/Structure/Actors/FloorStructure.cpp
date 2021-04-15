// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorStructure.h"
#include "Floor.h"
#include "Wall.h"
#include "../Data/Line.h"
#include "../../Settings/GlobalSettings.h"
#include "../Data/FloorDimensions.h"

AFloorStructure::AFloorStructure()
{

}

AFloorStructure::~AFloorStructure()
{

}

void AFloorStructure::Init(std::vector<Line>& wallLines, int floorPosition)
{
	m_floorPosition = floorPosition;
	//floors must be computed before Walls
	m_floorSegments = SpawnItems<AFloor>(1, m_floorClass);
	InitFloors(wallLines);
	//walls must be computed after floors
	m_wallSegments = SpawnItems<AWall>(wallLines.size(), m_wallClass);
	InitWalls(wallLines);
}

void AFloorStructure::DestroyAll(bool bNetForce, bool bShouldModifyLevel)
{
	for (int i = 0; i < m_wallSegments.size(); i++)
	{
		m_wallSegments.at(i)->DestroyAll(bNetForce, bShouldModifyLevel);
	}
	for (int i = 0; i < m_floorSegments.size(); i++)
	{
		m_floorSegments.at(i)->DestroyAll(bNetForce, bShouldModifyLevel);
	}
	Destroy(bNetForce, bShouldModifyLevel);
}

void AFloorStructure::BeginPlay()
{
	Super::BeginPlay();
}

void AFloorStructure::InitWalls(std::vector<Line>& wallLines)
{
	for (int i = 0; i < wallLines.size(); i++)
	{
		m_wallSegments.at(i)->InitVariables(wallLines.at(i), m_floorSegments, m_floorPosition);
	}
	for (auto& wall : m_wallSegments)
	{
		wall->SetVisible();
	}
}

void AFloorStructure::InitFloors(std::vector<Line>& wallLines)
{
	float minX = wallLines.at(0).GetPoint1().X;
	float maxX = wallLines.at(0).GetPoint1().X;
	float minY = wallLines.at(0).GetPoint1().Y;
	float maxY = wallLines.at(0).GetPoint1().Y;
	float height = wallLines.at(0).GetPoint1().Z;

	for (Line line : wallLines)
	{
		FVector p1 = line.GetPoint1();
		FVector p2 = line.GetPoint2();

		minX = std::min(minX, p1.X);
		minX = std::min(minX, p2.X);

		minY = std::min(minY, p1.Y);
		minY = std::min(minY, p2.Y);

		maxX = std::max(maxX, p1.X);
		maxX = std::max(maxX, p2.X);

		maxY = std::max(maxY, p1.Y);
		maxY = std::max(maxY, p2.Y);
	}

	for (auto floor : m_floorSegments)
	{
		std::vector<FloorDimensions> vec = std::vector<FloorDimensions>();
		vec.resize(1);
		vec.at(0) = FloorDimensions(FVector(minX, minY, height), FVector(minX, maxY, height), FVector(maxX, minY, height), FVector(maxX, maxY, height));
		floor->InitVariables(vec, m_floorPosition);
	}
	for (auto floor : m_floorSegments)
	{
		floor->SetVisible();
	}
}