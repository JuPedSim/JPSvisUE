// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorStructure.h"

AFloorStructure::AFloorStructure()
{
}

AFloorStructure::~AFloorStructure()
{
}

void AFloorStructure::BeginPlay()
{
	Super::BeginPlay();

	floorSegments = SpawnItems<AFloor*>(2, floorClass);
	PositionFloors();
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

void AFloorStructure::PositionFloors()
{
	for (AActor* floor : *floorSegments)
	{
		FRotator rotation = FRotator(rand() % 360, rand() % 360, rand() % 360);
		FVector translation = FVector(rand() % 10, rand() % 10, 0);
		FVector scaleing = FVector(rand() % 5, rand() % 5, rand() % 5);
		FTransform transform = FTransform(rotation, translation, scaleing);
		floor->SetActorTransform(transform);
	}

	for (AActor* floor : *floorSegments)
	{
		//floor->SetActorHiddenInGame(false);
	}
}