// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorStructure.h"
#include <sstream>

AFloorStructure::AFloorStructure()
{

}

AFloorStructure::~AFloorStructure()
{
}

void AFloorStructure::Init(std::vector<Line>* wallLines)
{
	//floors must be computed before Walls
	m_floorSegments = SpawnItems<AFloor*>(1, m_floorClass);
	InitFloors(wallLines);
	//walls must be computed after floors
	m_wallSegments = SpawnItems<AWall*>(wallLines->size(), m_wallClass);
	InitWalls(wallLines);
}

void AFloorStructure::BeginPlay()
{
	Super::BeginPlay();
}

AActor* AFloorStructure::SpawnItem(UClass* item)
{
	return GetWorld()->SpawnActor<AActor>(item, FVector(0.f), FRotator(0.f));
}


template <class T>
std::vector<T>* AFloorStructure::SpawnItems(int count, TSubclassOf<AActor> actorClass)
{
	std::vector<T>* vec = new std::vector<T>;
	vec->resize(count);
	for (int i = 0; i < count; i++)
	{
		vec->at(i) = (T)SpawnItem(actorClass);
	}
	return vec;
}

void AFloorStructure::InitWalls(std::vector<Line>* wallLines)
{
	for (int i = 0; i < wallLines->size(); i++)
	{
		m_wallSegments->at(i)->InitVariables(wallLines->at(i), m_floorSegments);
	}
	for (AWall* wall : *m_wallSegments)
	{
		wall->SetVisible();
	}
}

void AFloorStructure::InitFloors(std::vector<Line>* wallLines)
{
	float minX = wallLines->at(0).GetPoint1().X;
	float maxX = wallLines->at(0).GetPoint1().X;
	float minY = wallLines->at(0).GetPoint1().Y;
	float maxY = wallLines->at(0).GetPoint1().Y;
	float height = wallLines->at(0).GetPoint1().Z;

	for (Line line : *wallLines)
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

	for (AFloor* floor : *m_floorSegments)
	{
		std::vector<FloorDimensions>* vec = new std::vector<FloorDimensions>();
		vec->resize(1);
		vec->at(0) = FloorDimensions(FVector(minX,minY,height), FVector(minX, maxY, height), FVector(maxX, minY, height), FVector(maxX, maxY, height));
		floor->InitVariables(vec);
	}
	for (AFloor* floor : *m_floorSegments)
	{
		floor->SetVisible();
	}
}