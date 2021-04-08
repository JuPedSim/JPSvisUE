// Fill out your copyright notice in the Description page of Project Settings.


#include "Pedestrian.h"


// Sets default values
APedestrian::APedestrian()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_pedestrian = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(m_pedestrian);
}

void APedestrian::InitVariables(int id)
{
	m_id = id;
}

void APedestrian::SetVisible()
{
	SetActorHiddenInGame(false);
}

void APedestrian::SetPosition(FVector position)
{
	SetActorLocation(position* GlobalSettings::GetInstance()->GetScalingFactor());
}

void APedestrian::DestroyAll(bool bNetForce, bool bShouldModifyLevel)
{
	Destroy(bNetForce, bShouldModifyLevel);
}

// Called when the game starts or when spawned
void APedestrian::BeginPlay()
{
	Super::BeginPlay();

	GlobalSettings* settings = GlobalSettings::GetInstance();

	float objHeight = 100;
	float objWidth = 100;

	FRotator rotation = FRotator(0.f, 0.f, 0.f);
	FVector translation = FVector(0.f, 0.f, 0.f);
	float width = settings->GetPedestrianWidth()/objWidth;
	float height = settings->GetPedestrianHeight()/objHeight;
	FVector scaling = FVector(width,width,height);
	FTransform transform = FTransform(rotation, translation, scaling * settings->GetScalingFactor());
	SetActorTransform(transform);
}

// Called every frame
void APedestrian::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

