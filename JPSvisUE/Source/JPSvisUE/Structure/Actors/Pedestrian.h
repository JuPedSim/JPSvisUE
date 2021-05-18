// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BuildingActor.h"
#include "Pedestrian.generated.h"

struct Person;
UCLASS()
class JPSVISUE_API APedestrian : public ABuildingActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APedestrian();
	void InitVariables(int id, float creationTime);
	void SetVisible();
	void SetPosition(Person person, float timeInSec);
	void DestroyAll(bool bNetForce = false, bool bShouldModifyLevel = true);
	int GetID();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Building, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* m_pedestrian;
	int m_id;
	float m_animationPosition;
	float m_lastTimeInSec;
};
