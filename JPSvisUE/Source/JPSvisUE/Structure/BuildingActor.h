// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <vector>
#include "BuildingActor.generated.h"


UCLASS()
class JPSVISUE_API ABuildingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuildingActor();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void DestroyAll(bool bNetForce = false, bool bShouldModifyLevel = true);
	bool m_variablesInitialized = false;//todo maybe not used

	template <class T>
	T* SpawnItem(UClass* item)
	{
		return (T*)GetWorld()->SpawnActor<AActor>(item, FVector(0.f), FRotator(0.f));
	}

	template <class T>
	std::vector<T*> SpawnItems(int count, TSubclassOf<AActor> actorClass)
	{
		std::vector<T*> vec;
		vec.resize(count);
		for (int i = 0; i < count; i++)
		{
			vec.at(i) = SpawnItem<T>(actorClass);
		}
		return vec;
	}
};
