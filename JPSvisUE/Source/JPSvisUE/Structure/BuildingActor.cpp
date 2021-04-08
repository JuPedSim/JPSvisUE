// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingActor.h"

// Sets default values
ABuildingActor::ABuildingActor()
{
	//SetActorHiddenInGame(true);
}

// Called when the game starts or when spawned
void ABuildingActor::BeginPlay()
{
	Super::BeginPlay();
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}

void ABuildingActor::DestroyAll(bool bNetForce, bool bShouldModifyLevel)
{
	Destroy(bNetForce, bShouldModifyLevel);
}
