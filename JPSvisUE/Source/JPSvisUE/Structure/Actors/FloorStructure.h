// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <vector>
#include <memory>
#include "Floor.h"
#include "Wall.h"
#include "../Data/Line.h"
#include "../../Settings/GlobalSettings.h"
#include "../Data/FloorDimensions.h"
#include "FloorStructure.generated.h"


/**
 * 
 */
UCLASS()
class JPSVISUE_API AFloorStructure : public ABuildingActor
{
	GENERATED_BODY()
public:
	AFloorStructure();
	~AFloorStructure();
	void Init(std::vector<Line>& wallLines,int floorPosition);
	void DestroyAll(bool bNetForce = false, bool bShouldModifyLevel = true);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Building, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> m_floorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Building, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> m_wallClass;

	void InitFloors(std::vector<Line>& wallLines);

	void InitWalls(std::vector<Line>& wallLines);

	std::vector<AFloor*> m_floorSegments;

	std::vector<AWall*> m_wallSegments;

	int m_floorPosition;
};
