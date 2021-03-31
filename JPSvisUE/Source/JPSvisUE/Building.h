// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <vector>
#include "Floor.h"
#include "Line.h"
#include "BuildingActor.h"

#include "FloorStructure.h"
#include <stdlib.h>
#include "GlobalSettings.h"
#include "Cache.h"

#include "Building.generated.h"


UCLASS()
class JPSVISUE_API ABuilding : public ABuildingActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuilding();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Building, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> m_floorStructureClass;

	std::vector<AFloorStructure*> m_floors;

	Cache m_cache;
};
