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
	
	floors = SpawnItems<AFloor*>(2);
	PositionFloors();
}

// Called every frame
void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AActor* ABuilding::SpawnItem(UClass* item)
{
	return GetWorld()->SpawnActor<AActor>(item,FVector(0.f),FRotator(0.f));
}

template <class T>
vector<T>* ABuilding::SpawnItems(int count)
{
	vector<T>* vec = new vector<T>;
	vec->resize(count);
	for (int i = 0; i < count; i++)
	{
		vec->at(i) = (T)SpawnItem(floorClass);
	}
	return vec;
}

void ABuilding::PositionFloors()
{
	for (AActor* floor : *floors)
	{
		FRotator rotation = FRotator(rand() %360, rand() % 360, rand() % 360);
		FVector translation = FVector(rand()%10, rand() % 10, 0);
		FVector scaleing = FVector(rand()%5, rand()%5, rand()%5);
		FTransform transform = FTransform(rotation,translation,scaleing);
		floor->SetActorTransform(transform);
	}

	for (AActor* floor : *floors)
	{
		//floor->SetActorHiddenInGame(false);
	}
}


