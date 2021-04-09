// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include <vector>
#include "CoreMinimal.h"
#include "../BuildingActor.h"
#include "../Data/FloorDimensions.h"
#include "Floor.generated.h"

UCLASS()
class JPSVISUE_API AFloor : public ABuildingActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloor();
	void DestroyAll(bool bNetForce = false, bool bShouldModifyLevel = true);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void InitVariables(std::vector<FloorDimensions>& dims,int floorPosition);
	void SetVisible();

	std::vector<FloorDimensions>& GetDimensions();
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Building, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* m_floorMesh;

	std::vector<FloorDimensions> m_dimensions;

	int m_floorPosition;

	void SetPosition();

	void TickFloorViewTypeAll();
	void TickFloorViewTypeOnly();
	void TickFloorViewTypeAllBelow();
};
