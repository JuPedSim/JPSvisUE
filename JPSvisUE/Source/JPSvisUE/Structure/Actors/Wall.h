// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include <vector>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../BuildingActor.h"
#include "../Data/Line.h"
#include "Floor.h"
#include "../../Settings/GlobalSettings.h"
#include "DrawDebugHelpers.h"
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
	void InitVariables(Line line, std::vector<AFloor*>& connectedFloors);
	void SetVisible();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Building, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* m_wallMesh;

	std::vector<AFloor*> m_connectedFloors;
	Line m_wallLine;
	void SetPosition();
	void SetCamCheckPoints();
	void SetSmall(float DeltaTime);
	void SetBig(float DeltaTime);
	FVector ComputeViewObstructedVector(FVector dir);
	FVector2D m_normal;
	FVector2D m_direction;

	float m_scaleFactor;

	float m_scaleX;
	float m_scaleY;
	float m_scaleZbig;
	float m_scaleZsmall;
	
	std::vector<FVector> m_camCheckPoints;

	void TickViewTypeDynamic(float DeltaTime);
	void TickViewTypeSmall(float DeltaTime);
	void TickViewTypeBig(float DeltaTime);
};
