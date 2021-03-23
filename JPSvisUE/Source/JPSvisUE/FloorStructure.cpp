// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorStructure.h"
#include <sstream>

AFloorStructure::AFloorStructure()
{

}

AFloorStructure::~AFloorStructure()
{
}

void AFloorStructure::Init(vector<Line>* wallLines)
{
	//floors must be computed before Walls
	floorSegments = SpawnItems<AFloor*>(1, floorClass);
	InitFloors(wallLines);
	//walls must be computed after floors
	wallSegments = SpawnItems<AWall*>(wallLines->size(), wallClass);
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
vector<T>* AFloorStructure::SpawnItems(int count, TSubclassOf<AActor> actorClass)
{
	vector<T>* vec = new vector<T>;
	vec->resize(count);
	for (int i = 0; i < count; i++)
	{
		vec->at(i) = (T)SpawnItem(actorClass);
	}
	return vec;
}

void AFloorStructure::InitWalls(vector<Line>* wallLines)
{
	for (int i = 0; i < wallLines->size(); i++)
	{
		wallSegments->at(i)->InitVariables(wallLines->at(i), floorSegments);
	}
	for (AWall* wall : *wallSegments)
	{
		wall->SetVisible();
	}
}

void AFloorStructure::InitFloors(vector<Line>* wallLines)
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

		minX = min(minX, p1.X);
		minX = min(minX, p2.X);

		minY = min(minY, p1.Y);
		minY = min(minY, p2.Y);

		maxX = max(maxX, p1.X);
		maxX = max(maxX, p2.X);

		maxY = max(maxY, p1.Y);
		maxY = max(maxY, p2.Y);
	}

	for (AFloor* floor : *floorSegments)
	{
		vector<FloorDimensions>* vec = new vector<FloorDimensions>();
		vec->resize(1);
		vec->at(0) = FloorDimensions(FVector(minX,minY,height), FVector(minX, maxY, height), FVector(maxX, minY, height), FVector(maxX, maxY, height));
		floor->InitVariables(vec);
	}
	for (AFloor* floor : *floorSegments)
	{
		floor->SetVisible();
	}
}