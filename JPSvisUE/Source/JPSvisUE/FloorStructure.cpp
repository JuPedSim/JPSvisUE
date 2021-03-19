// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorStructure.h"

AFloorStructure::AFloorStructure()
{

}

AFloorStructure::~AFloorStructure()
{
}

void AFloorStructure::Init(vector<Line>* wallLines, float height)
{
	//floors must be computed before Walls
	floorSegments = SpawnItems<AFloor*>(1, floorClass);
	PositionFloors(wallLines, height);
	//walls must be computed after floors
	wallSegments = SpawnItems<AWall*>(wallLines->size(), wallClass);
	PositionWalls(wallLines, height);
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

void AFloorStructure::PositionWalls(vector<Line>* wallLines, float height)
{
	for (int i = 0; i < wallLines->size(); i++)
	{
		wallSegments->at(i)->InitVariables(wallLines->at(i), floorSegments);

		FVector p1 = wallLines->at(i).GetPoint1();
		FVector p2 = wallLines->at(i).GetPoint2();
		FVector vec = p2 - p1;
		FVector mittle = p1 + (vec * 0.5f);

		float length = sqrt((vec.X * vec.X) + (vec.Y * vec.Y));

		float objSize = 100;
		float sizeX = length * scalingFactor;
		float sizeY = wallThigness * scalingFactor;
		float sizeZ = wallHeight * scalingFactor;
		float scaleX = sizeX / objSize;
		float scaleY = sizeY / objSize;
		float scaleZ = sizeZ / objSize;
		float shiftX = mittle.X * scalingFactor;
		float shiftY = mittle.Y * scalingFactor;
		float shiftZ = (height * scalingFactor);
		float rot = ((atan2(vec.X, vec.Y) * 180) / PI) + 90.f;

		FRotator rotation = FRotator(0.f, rot, 0.f);
		FVector translation = FVector(shiftX, shiftY, shiftZ);
		FVector scaleing = FVector(scaleX, scaleY, scaleZ);
		FTransform transform = FTransform(rotation, translation, scaleing);
		wallSegments->at(i)->SetActorTransform(transform);
	}

	for (AActor* wall : *wallSegments)
	{
		wall->SetActorHiddenInGame(false);
	}
}

void AFloorStructure::PositionFloors(vector<Line>* wallLines, float height)
{
	float minX = numeric_limits<float>::max();
	float maxX = numeric_limits<float>::min();
	float minY = numeric_limits<float>::max();
	float maxY = numeric_limits<float>::min();

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
	float objSize = 100;
	float sizeX = (maxX - minX) * scalingFactor;
	float sizeY = (maxY - minY) * scalingFactor;
	float sizeZ = wallThigness * scalingFactor;
	float scaleX = sizeX / objSize;
	float scaleY = sizeY / objSize;
	float scaleZ = sizeZ / objSize;
	float shiftX = (minX * scalingFactor) + (0.5 * sizeX);
	float shiftY = (minY * scalingFactor) + (0.5 * sizeY);
	float shiftZ = (height * scalingFactor) - sizeZ;

	FRotator rotation = FRotator(0.f);
	FVector translation = FVector(shiftX, shiftY, shiftZ);
	FVector scaleing = FVector(scaleX, scaleY, scaleZ);
	FTransform transform = FTransform(rotation, translation, scaleing);
	floorSegments->at(0)->SetActorTransform(transform);
	vector<FloorDimensions>* vec = new vector<FloorDimensions>();
	vec->resize(1);
	vec->at(0) = FloorDimensions();
	floorSegments->at(0)->InitVariables(vec);
	floorSegments->at(0)->SetActorHiddenInGame(false);
}