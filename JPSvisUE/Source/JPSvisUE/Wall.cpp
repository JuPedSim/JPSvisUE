// Fill out your copyright notice in the Description page of Project Settings.


#include "Wall.h"

// Sets default values
AWall::AWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	wallMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(wallMesh);
}

// Called when the game starts or when spawned
void AWall::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWall::InitVariables(Line line, vector<AFloor*>* floors)
{
	wallLine = line;
	connectedFloors = floors;
	//last operation
	variablesInitialized = true;
}

