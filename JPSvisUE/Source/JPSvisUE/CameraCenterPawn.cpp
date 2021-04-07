// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraCenterPawn.h"


// Sets default values
ACameraCenterPawn::ACameraCenterPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	m_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh")); 

	RootComponent = m_mesh;

	m_springArm->AttachTo(RootComponent);
	m_springArm->TargetArmLength = 350.f;
	m_springArm->SetWorldRotation(FRotator(-60.f,0,0));

	m_camera->AttachTo(m_springArm,USpringArmComponent::SocketName);

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	m_lastDirection = FVector2D(1,0);
	
}

// Called when the game starts or when spawned
void ACameraCenterPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraCenterPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator newRot = m_springArm->GetComponentRotation();
	float yaw = newRot.Yaw + m_rotationInput.X;
	newRot.Yaw = (int)yaw % 360 + yaw - (float)(int)yaw;
	newRot.Pitch = FMath::Clamp(newRot.Pitch + m_rotationInput.Y,-80.f,0.f);
	m_springArm->SetWorldRotation(newRot);

	FVector dir3D = newRot.Vector();
	FVector2D dir2D = FVector2D(dir3D.X,dir3D.Y);
	if (dir2D.IsZero()) 
	{
		dir2D = m_lastDirection;
	}
	else
	{
		dir2D.Normalize();
		m_lastDirection = dir2D;
	}

	GlobalSettings* settings = GlobalSettings::GetInstance();

	float height = settings->GetFloorHeights().at(0)+settings->GetCamOffsetFromFloor();
	if (settings->GetFloorHeights().size()>settings->GetFloorPosition().GetPosition())
	{
		height = settings->GetFloorHeights().at(settings->GetFloorPosition().GetPosition())+ settings->GetCamOffsetFromFloor();
	}
	height = height * settings->GetScalingFactor();

	FVector newPos = m_mesh->GetComponentLocation();
	newPos += m_positionInput.Y * FVector(dir2D,0);
	newPos += m_positionInput.X * FVector(dir2D.Y,-dir2D.X,0);
	newPos.Z = height;
	m_mesh->SetWorldLocation(newPos);

	m_springArm->TargetArmLength = FMath::Clamp(m_springArm->TargetArmLength + m_zoomInput, GlobalSettings::GetInstance()->GetCameraSpringArmLengthMin(), GlobalSettings::GetInstance()->GetCameraSpringArmLengthMax());
}

// Called to bind functionality to input
void ACameraCenterPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("Yaw", this, &ACameraCenterPawn::Yaw);
	InputComponent->BindAxis("Pitch", this, &ACameraCenterPawn::Pitch);
	InputComponent->BindAxis("ForwardBackward", this, &ACameraCenterPawn::ForwardBackward);
	InputComponent->BindAxis("LeftRight", this, &ACameraCenterPawn::LeftRight);
	InputComponent->BindAxis("Zoom", this, &ACameraCenterPawn::Zoom);
}

void ACameraCenterPawn::Pitch(float axis)
{
	m_rotationInput.Y = axis* GlobalSettings::GetInstance()->GetPitchSpeed();
}

void ACameraCenterPawn::Yaw(float axis)
{
	m_rotationInput.X = axis * GlobalSettings::GetInstance()->GetYawSpeed();
}

void ACameraCenterPawn::ForwardBackward(float axis)
{
	m_positionInput.Y = axis * GlobalSettings::GetInstance()->GetMovementSpeed();
}

void ACameraCenterPawn::LeftRight(float axis)
{
	m_positionInput.X = axis * GlobalSettings::GetInstance()->GetMovementSpeed();
}

void ACameraCenterPawn::Zoom(float axis)
{
	m_zoomInput = axis * GlobalSettings::GetInstance()->GetZoomSpeed();
}

