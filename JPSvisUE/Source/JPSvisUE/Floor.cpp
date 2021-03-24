// Fill out your copyright notice in the Description page of Project Settings.


#include "Floor.h"

// Sets default values
AFloor::AFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	floorMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(floorMesh);
}

// Called when the game starts or when spawned
void AFloor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFloor::InitVariables(vector<FloorDimensions>* dims)
{
	dimensions = dims;
	this->SetPosition();
	//last operation
	variablesInitialized = true;
}

void AFloor::SetVisible()
{
	this->SetActorHiddenInGame(false);
}

vector<FloorDimensions>* AFloor::GetDimensions()
{
	return dimensions;
}

void AFloor::SetPosition()
{
	GlobalSettings* settings = GlobalSettings::GetInstance();

	float minX = this->dimensions->at(0).GetMinXminY().X;
	float maxX = this->dimensions->at(0).GetMaxXmaxY().X;
	float minY = this->dimensions->at(0).GetMinXminY().Y;
	float maxY = this->dimensions->at(0).GetMaxXmaxY().Y;
	float height = this->dimensions->at(0).GetMinXminY().Z;
	float objSize = 100;
	float sizeX = (maxX - minX) * settings->GetScalingFactor();
	float sizeY = (maxY - minY) * settings->GetScalingFactor();
	float sizeZ = settings->GetFloorThigness() * settings->GetScalingFactor();
	float scaleX = sizeX / objSize;
	float scaleY = sizeY / objSize;
	float scaleZ = sizeZ / objSize;
	float shiftX = (minX * settings->GetScalingFactor()) + (0.5 * sizeX);
	float shiftY = (minY * settings->GetScalingFactor()) + (0.5 * sizeY);
	float shiftZ = (height * settings->GetScalingFactor()) - sizeZ;

	FRotator rotation = FRotator(0.f);
	FVector translation = FVector(shiftX, shiftY, shiftZ);
	FVector scaleing = FVector(scaleX, scaleY, scaleZ);
	FTransform transform = FTransform(rotation, translation, scaleing);
	this->SetActorTransform(transform);
}

