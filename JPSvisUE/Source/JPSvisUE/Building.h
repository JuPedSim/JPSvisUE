// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <vector>
#include "Floor.h"
#include "Line.h"
#include "FloorStructure.h"
#include <stdlib.h>

#include "Building.generated.h"

UCLASS()
class JPSVISUE_API ABuilding : public AActor
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

	AActor* SpawnItem(UClass* item);
	template <class T>
	std::vector<T>* SpawnItems(int count, TSubclassOf<AActor> actorClass);

	std::vector<AFloorStructure*>* m_floors;
};
