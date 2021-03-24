// Fill out your copyright notice in the Description page of Project Settings.
using namespace std;
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <vector>
#include "Floor.h"
#include "Wall.h"
#include "Line.h"
#include "GlobalSettings.h"
#include "FloorDimensions.h"
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
	void Init(vector<Line>* wallLines);
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

	void InitFloors(vector<Line>* wallLines);

	void InitWalls(vector<Line>* wallLines);

	vector<AFloor*>* floorSegments;

	vector<AWall*>* wallSegments;

};
