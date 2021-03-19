// Fill out your copyright notice in the Description page of Project Settings.
using namespace std;
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <vector>
#include "Floor.h"
#include "Wall.h"
#include "FloorStructure.generated.h"

/**
 * 
 */
UCLASS()
class JPSVISUE_API AFloorStructure : public AActor
{
	GENERATED_BODY()
public:
	AFloorStructure();
	~AFloorStructure();
	void Init();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Building, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> floorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Building, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> wallClass;

	AActor* SpawnItem(UClass* item);
	template <class T>
	vector<T>* SpawnItems(int count, TSubclassOf<AActor> actorClass);

	void PositionFloors();

	void PositionWalls();

	vector<AFloor*>* floorSegments;

	vector<AWall*>* wallSegments;
};
