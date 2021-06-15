// Fill out your copyright notice in the Description page of Project Settings.
using namespace std;

#pragma once

#include <vector>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildingActor.h"
#include "Line.h"
#include "Floor.h"
#include "Wall.generated.h"


UCLASS()
class JPSVISUE_API AWall : public ABuildingActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void InitVariables(Line line,vector<AFloor*>* connectedFloors);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Building, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* wallMesh;

	vector<AFloor*>* connectedFloors;
	Line wallLine;
};
