// Fill out your copyright notice in the Description page of Project Settings.


#include "Wall.h"

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
	APlayerCameraManager* cam = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	FVector camLocation = cam->GetCameraLocation();
	

	
	bool renderSmall = false;
	for (FVector v : *this->camCheckPoints)
	{
		FVector dir = v - camLocation;
		dir.Normalize(); //todo could not normalize catch
		FVector checkV = this->ComputeViewObstructedVector(dir);
		for (AFloor* floor : *this->connectedFloors)
		{
			vector<FloorDimensions>* fD = floor->GetDimensions();
			for (FloorDimensions &dim : *fD)
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
					float obstractionDegree = (atan(lengthHor/ lengthVer)/(2.f*PI))*360.f;
					if (obstractionDegree> allowedObstractionDegree)
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

	float length = sqrt((vec.X * vec.X) + (vec.Y * vec.Y));

	float objSize = 100;
	float sizeX = length * scalingFactor;
	float sizeY = zeroVal;
	float sizeZbig = wallBigHeight * scalingFactor;
	float sizeZsmall = wallSmallHeight * scalingFactor;
	float scaleX = sizeX / objSize;
	float scaleY = sizeY / objSize;
	float scaleZbig = sizeZbig / objSize;
	float scaleZsmall = sizeZsmall / objSize;
	float shiftX = mittle.X * scalingFactor;
	float shiftY = mittle.Y * scalingFactor;
	float shiftZ = p1.Z * scalingFactor;
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
	FVector p1 = this->wallLine.GetPoint1();
	FVector p2 = this->wallLine.GetPoint2();
	FVector p1u = FVector(p1.X, p1.Y, p1.Z + wallBigHeight);
	FVector p2u = FVector(p2.X, p2.Y, p2.Z + wallBigHeight);
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
	float x = dir.X;
	float y = dir.Y;
	float lengthHor = sqrt(x*x+y*y);

	float lenghtVer = lengthHor/tan((viewObstractedCheckerDegree/360)*2.f*PI);

	FVector v = FVector(x, y, -lenghtVer);
	v.Normalize();
	return v;
}

