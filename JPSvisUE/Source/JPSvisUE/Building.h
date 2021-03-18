// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
using namespace std;

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <vector>
#include "Floor.h"
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
	TSubclassOf<AActor> floorClass;

	AActor* SpawnItem(UClass * item);
	template <class T>
	vector<T>*SpawnItems(int count);
	void PositionFloors();

	vector<AFloor*>* floors;
};
