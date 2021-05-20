// Fill out your copyright notice in the Description page of Project Settings.


#include "Pedestrian.h"
#include "../../DataManagment/Cache/CacheEntry.h"
#include "../../Settings/GlobalSettings.h"

// Sets default values
APedestrian::APedestrian()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_pedestrian = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(m_pedestrian);
	m_lastTimeInSec = 0;
	m_animationPosition = (float)rand() / RAND_MAX;
}

void APedestrian::InitVariables(int id,float creationTime, FVector intialPosition)
{
	m_id = id;
	m_lastTimeInSec = creationTime;
	m_lastPosition = intialPosition;
}

void APedestrian::SetVisible()
{
	SetActorHiddenInGame(false);
}

void APedestrian::SetPosition(Person person,float timeInSec)
{
	GlobalSettings* settings = GlobalSettings::GetInstance();

	float changePerUnitTraveled = settings->GetAnimationChangePerUnitTraveled();

	FVector pos = FVector(person.x, person.y, person.z);

	float delta = (m_lastPosition - pos).Size();
	float change = delta * changePerUnitTraveled;
	float newAnimationPosition = m_animationPosition + change;
	float temp;
	newAnimationPosition = modf(newAnimationPosition, &temp);
	m_animationPosition = newAnimationPosition;
	m_lastTimeInSec = timeInSec;
	m_lastPosition = pos;

	float t = m_animationPosition * 2;
	if (t>1) 
	{
		t = 2 - t;
	}
	t = t * 0.2;

	float objHeight = 100;
	float objWidth = 100;
	float width = settings->GetPedestrianWidth() / objWidth;
	float height = settings->GetPedestrianHeight() / objHeight;

	FRotator rotation = FRotator(0, person.rotationAngle, 0);
	FVector translation = pos * settings->GetScalingFactor();
	FVector scaling = FVector(width + width * t, width - width * t, height) * settings->GetScalingFactor();

	FTransform transform = FTransform(rotation, translation, scaling);
	SetActorTransform(transform);
}

void APedestrian::DestroyAll(bool bNetForce, bool bShouldModifyLevel)
{
	Destroy(bNetForce, bShouldModifyLevel);
}

int APedestrian::GetID()
{
	return m_id;
}

// Called when the game starts or when spawned
void APedestrian::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APedestrian::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

