// Fill out your copyright notice in the Description page of Project Settings.
using namespace std;
#pragma once

#include <vector>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildingActor.h"
#include "FloorDimensions.h"
#include "Floor.generated.h"

UCLASS()
class JPSVISUE_API AFloor : public ABuildingActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void InitVariables(vector<FloorDimensions>* dims);

	vector<FloorDimensions>* GetDimensions();
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Building, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* floorMesh;

	vector<FloorDimensions>* dimensions;
};
