// Fill out your copyright notice in the Description page of Project Settings.


#include "Wall.h"
#include <sstream>

// Sets default values
AWall::AWall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	wallMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(wallMesh);

	this->scaleZsmallTransform = FVector(0.f);
	this->scaleZbigTransform = FVector(0.f);
}

// Called when the game starts or when spawned
void AWall::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (GlobalSettings::GetInstance()->GetViewType())
	{
	case LARGE_VIEW:
		this->TickViewTypeBig();
		break;
	case SMALL_VIEW:
		this->TickViewTypeSmall();
		break;
	case DYNAMIC_VIEW:
		this->TickViewTypeDynamic();
		break;
	default:
		break;
	}
}

void AWall::InitVariables(Line line, vector<AFloor*>* floors)
{
	FVector temp = line.GetPoint2() - line.GetPoint1();
	this->direction = FVector2D(temp.X, temp.Y);
	this->normal = FVector2D(temp.Y,-temp.X);
	this->direction.Normalize();
	this->normal.Normalize();
	this->wallLine = line;
	this->connectedFloors = floors;

	this->SetCamCheckPoints();
	this->SetPosition();



	//last operation
	variablesInitialized = true;//todo maybe not used
}

void AWall::SetVisible()
{
	this->SetActorHiddenInGame(false);
}

void AWall::SetPosition()
{
	FVector p1 = this->wallLine.GetPoint1();
	FVector p2 = this->wallLine.GetPoint2();
	FVector vec = p2 - p1;
	FVector mittle = p1 + (vec * 0.5f);

	GlobalSettings* settings = GlobalSettings::GetInstance();

	float length = sqrt((vec.X * vec.X) + (vec.Y * vec.Y));

	float objSize = 100;
	float sizeX = length * settings->GetScalingFactor();
	float sizeY = 0.00001f;
	float sizeZbig = settings->GetWallBigHeight() * settings->GetScalingFactor();
	float sizeZsmall = settings->GetWallSmallHeight() * settings->GetScalingFactor();
	float scaleX = sizeX / objSize;
	float scaleY = sizeY / objSize;
	float scaleZbig = sizeZbig / objSize;
	float scaleZsmall = sizeZsmall / objSize;
	float shiftX = mittle.X * settings->GetScalingFactor();
	float shiftY = mittle.Y * settings->GetScalingFactor();
	float shiftZ = p1.Z * settings->GetScalingFactor();
	float rot = ((atan2(vec.X, vec.Y) * 180) / PI) + 90.f;

	FRotator rotation = FRotator(0.f, rot, 0.f);
	FVector translation = FVector(shiftX, shiftY, shiftZ);
	this->scaleZbigTransform = FVector(scaleX, scaleY, scaleZbig);
	this->scaleZsmallTransform = FVector(scaleX, scaleY, scaleZsmall);
	FTransform transform = FTransform(rotation, translation, this->scaleZbigTransform);
	this->SetActorTransform(transform);
	this->isBig = true;
}

void AWall::SetCamCheckPoints()
{
	GlobalSettings* settings = GlobalSettings::GetInstance();

	FVector p1 = this->wallLine.GetPoint1();
	FVector p2 = this->wallLine.GetPoint2();
	FVector p1u = FVector(p1.X, p1.Y, p1.Z + settings->GetWallBigHeight());
	FVector p2u = FVector(p2.X, p2.Y, p2.Z + settings->GetWallBigHeight());
	FVector pMu = p1u + 0.5 * (p2u - p1u);
	this->camCheckPoints = new vector<FVector>();
	this->camCheckPoints->resize(1);
	this->camCheckPoints->at(0) = pMu;
}

void AWall::SetSmall()
{
	if (this->isBig)
	{
		this->SetActorScale3D(this->scaleZsmallTransform);
	}
	this->isBig = false;
}

void AWall::SetBig()
{
	if (!this->isBig)
	{
		this->SetActorScale3D(this->scaleZbigTransform);
	}
	this->isBig = true;
}

FVector AWall::ComputeViewObstructedVector(FVector dir)
{
	GlobalSettings* settings = GlobalSettings::GetInstance();

	float x = dir.X;
	float y = dir.Y;
	float lengthHor = sqrt(x*x+y*y);

	float lenghtVer = lengthHor/tan((settings->GetViewObstractedCheckerDegree()/360)*2.f*PI);

	FVector v = FVector(x, y, -lenghtVer);
	v.Normalize();
	return v;
}

void AWall::TickViewTypeDynamic()
{
	GlobalSettings* settings = GlobalSettings::GetInstance();

	APlayerCameraManager* cam = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	FVector camLocation = cam->GetCameraLocation() / settings->GetScalingFactor();
	bool renderSmall = false;
	for (FVector v : *this->camCheckPoints)
	{
		FVector dir = v - camLocation;
		dir.Normalize(); //todo could not normalize catch
		FVector checkV = this->ComputeViewObstructedVector(dir);
		/*DrawDebugLine(this->GetWorld(),v* scalingFactor,(v+checkV*10)* scalingFactor,FColor(255,0,0,0),false,1.0f,(uint8)'\000',5);
		DrawDebugLine(this->GetWorld(), v * scalingFactor, (v + FVector(dir.X,dir.Y,0) * 10) * scalingFactor, FColor(0, 255, 0, 0), false, 1.0f, (uint8)'\000', 5);
		*/

		for (AFloor* floor : *this->connectedFloors)
		{
			vector<FloorDimensions>* fD = floor->GetDimensions();
			for (FloorDimensions& dim : *fD)
			{
				if (dim.checkCollision(v, checkV))
				{
					//in 2 dimesions
					//dir = a*direction + b*normal
					//b = (dirX-dirY*directionX)/(normalX*directionY + normalY*directionX)
					//b = dir part in normal direction
					float b = (dir.X - dir.Y * this->direction.X) / (this->normal.X * this->direction.Y + this->normal.Y * this->direction.X);
					float lengthHor = abs(b);
					float lengthVer = abs(dir.Z);
					float obstractionDegree = (atan(lengthHor / lengthVer) / (2.f * PI)) * 360.f;
					if (obstractionDegree > settings->GetAllowedObstractionDegree())
					{
						renderSmall = true;
					}
				}
			}
		}
	}
	if (renderSmall)
	{
		this->SetSmall();
	}
	else
	{
		this->SetBig();
	}
}

void AWall::TickViewTypeSmall()
{
	this->SetSmall();
}

void AWall::TickViewTypeBig()
{
	this->SetBig();
}

