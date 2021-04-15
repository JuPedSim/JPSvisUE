// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <Runtime/Engine/Classes/GameFramework/SpringArmComponent.h>
#include <Runtime/Engine/Classes/Camera/CameraComponent.h>
#include "CameraCenterPawn.generated.h"


UCLASS()
class JPSVISUE_API ACameraCenterPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACameraCenterPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere)
		USpringArmComponent* m_springArm;
	UCameraComponent* m_camera;

	UPROPERTY(EditAnywhere);
	UStaticMeshComponent* m_mesh;

	FVector2D m_rotationInput;
	FVector2D m_positionInput;
	float m_zoomInput;
	FVector2D m_lastDirection;

	void Pitch(float axis);
	void Yaw(float axis);
	void ForwardBackward(float axis);
	void LeftRight(float axis);
	void Zoom(float axis);
};
