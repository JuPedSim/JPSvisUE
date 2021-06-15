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

	float h1 = 20;
	float h2 = 40;

	std::vector<Line>* lines1 = new std::vector<Line>();
	lines1->resize(7);
	lines1->at(0) = Line(FVector(-10, -10, 0.f), FVector(-10, 70, 0.f));
	lines1->at(1) = Line(FVector(-10, 70, 0.f), FVector(30, 70, 0.f));
	lines1->at(2) = Line(FVector(30, 70, 0.f), FVector(30, 50, 0.f));
	lines1->at(3) = Line(FVector(30, 50, 0.f), FVector(60, 50, 0.f));
	lines1->at(4) = Line(FVector(60, 50, 0.f), FVector(60, -10, 0.f));
	lines1->at(5) = Line(FVector(60, -10, 0.f), FVector(-10, -10, 0.f));
	lines1->at(6) = Line(FVector(30, -10, 0.f), FVector(30, 20, 0.f));

	std::vector<Line>* lines2 = new std::vector<Line>();
	lines2->resize(7);
	lines2->at(0) = Line(FVector(-10, -10, h1), FVector(-10, 70, h1));
	lines2->at(1) = Line(FVector(-10, 70, h1), FVector(30, 70, h1));
	lines2->at(2) = Line(FVector(30, 70, h1), FVector(30, 50, h1));
	lines2->at(3) = Line(FVector(30, 50, h1), FVector(60, 50, h1));
	lines2->at(4) = Line(FVector(60, 50, h1), FVector(60, -10, h1));
	lines2->at(5) = Line(FVector(60, -10, h1), FVector(-10, -10, h1));
	lines2->at(6) = Line(FVector(30, -10, h1), FVector(30, 20, h1));

	std::vector<Line>* lines3 = new std::vector<Line>();
	lines3->resize(7);
	lines3->at(0) = Line(FVector(-10, -10, h2), FVector(-10, 70, h2));
	lines3->at(1) = Line(FVector(-10, 70, h2), FVector(30, 70, h2));
	lines3->at(2) = Line(FVector(30, 70, h2), FVector(30, 50, h2));
	lines3->at(3) = Line(FVector(30, 50, h2), FVector(60, 50, h2));
	lines3->at(4) = Line(FVector(60, 50, h2), FVector(60, -10, h2));
	lines3->at(5) = Line(FVector(60, -10, h2), FVector(-10, -10, h2));
	lines3->at(6) = Line(FVector(30, -10, h2), FVector(30, 20, h2));

	m_floors = SpawnItems<AFloorStructure*>(3, m_floorStructureClass);
	m_floors->at(0)->Init(lines1);
	m_floors->at(1)->Init(lines2);
	m_floors->at(2)->Init(lines3);
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
std::vector<T>* ABuilding::SpawnItems(int count, TSubclassOf<AActor> actorClass)
{
	std::vector<T>* vec = new std::vector<T>;
	vec->resize(count);
	for (int i = 0; i < count; i++)
	{
		vec->at(i) = (T)SpawnItem(actorClass);
	}
	return vec;
}


