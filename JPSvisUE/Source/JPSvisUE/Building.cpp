// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"

// Sets default values
ABuilding::ABuilding()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABuilding::BeginPlay()
{
	Super::BeginPlay();

	vector<Line>* lines = new vector<Line>();
	lines->resize(7);
	lines->at(0) = Line(FVector(-10, -10, 0.f), FVector(-10, 70, 0.f));
	lines->at(1) = Line(FVector(-10, 70, 0.f), FVector(30, 70, 0.f));
	lines->at(2) = Line(FVector(30, 70, 0.f), FVector(30, 50, 0.f));
	lines->at(3) = Line(FVector(30, 50, 0.f), FVector(60, 50, 0.f));
	lines->at(4) = Line(FVector(60, 50, 0.f), FVector(60, -10, 0.f));
	lines->at(5) = Line(FVector(60, -10, 0.f), FVector(-10, -10, 0.f));
	lines->at(6) = Line(FVector(30, -10, 0.f), FVector(30, 20, 0.f));

	floors = SpawnItems<AFloorStructure*>(1, floorStructureClass);
	for (AFloorStructure* floor : *floors)
	{
		floor->Init(lines);
	}
}

// Called every frame
void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

AActor* ABuilding::SpawnItem(UClass* item)
{
	return GetWorld()->SpawnActor<AActor>(item, FVector(0.f), FRotator(0.f));
}


template <class T>
vector<T>* ABuilding::SpawnItems(int count, TSubclassOf<AActor> actorClass)
{
	vector<T>* vec = new vector<T>;
	vec->resize(count);
	for (int i = 0; i < count; i++)
	{
		vec->at(i) = (T)SpawnItem(actorClass);
	}
	return vec;
}


