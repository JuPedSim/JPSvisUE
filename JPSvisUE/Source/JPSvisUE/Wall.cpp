// Fill out your copyright notice in the Description page of Project Settings.


#include "Wall.h"

// Sets default values
AWall::AWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	wallMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(wallMesh);

	this->scaleZsmallTransform = FVector(0.f);
	this->scaleZbigTransform = FVector(0.f);
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

	this->SetPosition();

	//last operation
	variablesInitialized = true;//todo maybe not used
}

void AWall::SetVisible()
{
	this->SetActorHiddenInGame(false);
}

void AWall::SetPosition()
{
	FVector p1 = this->wallLine.GetPoint1();
	FVector p2 = this->wallLine.GetPoint2();
	FVector vec = p2 - p1;
	FVector mittle = p1 + (vec * 0.5f);

	float length = sqrt((vec.X * vec.X) + (vec.Y * vec.Y));

	float objSize = 100;
	float sizeX = length * scalingFactor;
	float sizeY = zeroVal;
	float sizeZbig = wallBigHeight * scalingFactor;
	float sizeZsmall = wallSmallHeight * scalingFactor;
	float scaleX = sizeX / objSize;
	float scaleY = sizeY / objSize;
	float scaleZbig = sizeZbig / objSize;
	float scaleZsmall = sizeZsmall / objSize;
	float shiftX = mittle.X * scalingFactor;
	float shiftY = mittle.Y * scalingFactor;
	float shiftZ = p1.Z * scalingFactor;
	float rot = ((atan2(vec.X, vec.Y) * 180) / PI) + 90.f;

	FRotator rotation = FRotator(0.f, rot, 0.f);
	FVector translation = FVector(shiftX, shiftY, shiftZ);
	this->scaleZbigTransform = FVector(scaleX, scaleY, scaleZbig);
	this->scaleZsmallTransform = FVector(scaleX, scaleY, scaleZsmall);
	FTransform transform = FTransform(rotation, translation, this->scaleZbigTransform);
	this->SetActorTransform(transform);
}

void AWall::SetSmall()
{
	this->SetActorScale3D(this->scaleZsmallTransform);
}

void AWall::SetBig()
{
	this->SetActorScale3D(this->scaleZbigTransform);
}

