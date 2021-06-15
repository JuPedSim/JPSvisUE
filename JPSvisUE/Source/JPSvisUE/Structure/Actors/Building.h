// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "../BuildingActor.h"
#include <vector>
#include <stdlib.h>
#include "../../DataManagment/Cache/Cache.h"
#include "Building.generated.h"

class AFloorStructure;
class APedestrian;

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
	void DestroyAll(bool bNetForce = false, bool bShouldModifyLevel = true);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Building, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AActor> m_floorStructureClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Building, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AActor> m_pedestrianClass;

	std::vector<AFloorStructure*> m_floors;
	std::vector<APedestrian*> m_pedestrians;

	Cache m_cache;
	bool m_cacheIsSet;

	void SetAutoPlayFrame(float delta);
	void LoadPedestrians();
	void LoadStructure();
	void MovePedestrians();


	bool GetShouldBeHidden(float height);
};
