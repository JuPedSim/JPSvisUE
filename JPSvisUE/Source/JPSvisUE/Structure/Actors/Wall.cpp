// Fill out your copyright notice in the Description page of Project Settings.


#include "Wall.h"

// Sets default values
AWall::AWall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_wallMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(m_wallMesh);

	m_scaleX = 0;
	m_scaleY = 0;
	m_scaleZbig = 0;
	m_scaleZsmall = 0;
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

	switch (GlobalSettings::GetInstance()->GetFloorViewType())
	{
	case FloorViewType::ALL_BELOW_VIEW:
		TickFloorViewTypeAllBelow();
		break;
	case FloorViewType::ALL_VIEW:
		TickFloorViewTypeAll();
		break;
	case FloorViewType::ONLY_VIEW:
		TickFloorViewTypeOnly();
		break;
	default:
		break;
	}

	switch (GlobalSettings::GetInstance()->GetWallViewType())
	{
	case WallViewType::LARGE_VIEW:
		TickWallViewTypeBig(DeltaTime);
		break;
	case WallViewType::SMALL_VIEW:
		TickWallViewTypeSmall(DeltaTime);
		break;
	case WallViewType::DYNAMIC_VIEW:
		TickWallViewTypeDynamic(DeltaTime);
		break;
	default:
		break;
	}
}

void AWall::InitVariables(Line line, std::vector<AFloor*>& connectedFloors, int floorPosition)
{
	m_floorPosition = floorPosition;

	FVector temp = line.GetPoint2() - line.GetPoint1();
	m_direction = FVector2D(temp.X, temp.Y);
	m_normal = FVector2D(temp.Y,-temp.X);
	m_direction.Normalize();
	m_normal.Normalize();
	m_wallLine = line;
	m_connectedFloors = connectedFloors;

	SetCamCheckPoints();
	SetPosition();



	//last operation
	m_variablesInitialized = true;//todo maybe not used
}

void AWall::SetVisible()
{
	SetActorHiddenInGame(false);
}

void AWall::SetPosition()
{
	FVector p1 = m_wallLine.GetPoint1();
	FVector p2 = m_wallLine.GetPoint2();
	FVector vec = p2 - p1;
	FVector mittle = p1 + (vec * 0.5f);

	GlobalSettings* settings = GlobalSettings::GetInstance();

	float length = sqrt((vec.X * vec.X) + (vec.Y * vec.Y));

	float objSize = 100;
	float sizeX = length * settings->GetScalingFactor();
	float sizeY = 0.001f;
	float sizeZbig = settings->GetWallBigHeight() * settings->GetScalingFactor();
	float sizeZsmall = settings->GetWallSmallHeight() * settings->GetScalingFactor();
	m_scaleX = sizeX / objSize;
	m_scaleY = sizeY / objSize;
	m_scaleZbig = sizeZbig / objSize;
	m_scaleZsmall = sizeZsmall / objSize;
	float shiftX = mittle.X * settings->GetScalingFactor();
	float shiftY = mittle.Y * settings->GetScalingFactor();
	float shiftZ = p1.Z * settings->GetScalingFactor();
	float rot = ((atan2(vec.X, vec.Y) * 180) / PI) + 90.f;

	FRotator rotation = FRotator(0.f, rot, 0.f);
	FVector translation = FVector(shiftX, shiftY, shiftZ);
	FTransform transform = FTransform(rotation, translation, FVector(m_scaleX, m_scaleY, m_scaleZbig));
	SetActorTransform(transform);
	m_scaleFactor = 1;
}

void AWall::SetCamCheckPoints()
{
	GlobalSettings* settings = GlobalSettings::GetInstance();

	FVector p1 = m_wallLine.GetPoint1();
	FVector p2 = m_wallLine.GetPoint2();
	FVector p1u = FVector(p1.X, p1.Y, p1.Z + settings->GetWallBigHeight());
	FVector p2u = FVector(p2.X, p2.Y, p2.Z + settings->GetWallBigHeight());
	FVector pMu = p1u + 0.5 * (p2u - p1u);
	m_camCheckPoints = std::vector<FVector>();
	m_camCheckPoints.resize(1);
	m_camCheckPoints.at(0) = pMu;
}

void AWall::SetSmall(float DeltaTime)
{
	if (m_scaleFactor>0)
	{
		GlobalSettings* settings = GlobalSettings::GetInstance();
		
		float sZ;
		if (DeltaTime==-1) 
		{
			sZ = m_scaleZsmall;
			m_scaleFactor = 0;
		}
		else
		{
			float change = -DeltaTime * settings->GetWallScaleChangeSpeed();
			m_scaleFactor = std::max(change + m_scaleFactor,0.f);
			float range = m_scaleZbig - m_scaleZsmall;
			sZ= m_scaleZsmall + m_scaleFactor * range;
		}
		SetActorScale3D(FVector(m_scaleX, m_scaleY,sZ));
	}
}

void AWall::SetBig(float DeltaTime)
{
	if (m_scaleFactor<1)
	{
		GlobalSettings *settings = GlobalSettings::GetInstance();

		float sZ;
		if (DeltaTime == -1)
		{
			sZ = m_scaleZbig;
			m_scaleFactor = 1;
		}
		else
		{
			float change = DeltaTime * settings->GetWallScaleChangeSpeed();
			m_scaleFactor = std::min(change + m_scaleFactor, 1.f);
			float range = m_scaleZbig - m_scaleZsmall;
			sZ = m_scaleZsmall + m_scaleFactor * range;
		}
		this->SetActorScale3D(FVector(m_scaleX, m_scaleY, sZ));
	}
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

void AWall::TickWallViewTypeDynamic(float DeltaTime)
{
	GlobalSettings* settings = GlobalSettings::GetInstance();

	APlayerCameraManager* cam = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	FVector camLocation = cam->GetCameraLocation() / settings->GetScalingFactor();
	bool renderSmall = false;
	for (FVector v : m_camCheckPoints)
	{
		FVector dir = v - camLocation;
		dir.Normalize(); //todo could not normalize catch
		FVector checkV = ComputeViewObstructedVector(dir);
		/*DrawDebugLine(this->GetWorld(),v* scalingFactor,(v+checkV*10)* scalingFactor,FColor(255,0,0,0),false,1.0f,(uint8)'\000',5);
		DrawDebugLine(this->GetWorld(), v * scalingFactor, (v + FVector(dir.X,dir.Y,0) * 10) * scalingFactor, FColor(0, 255, 0, 0), false, 1.0f, (uint8)'\000', 5);
		*/

		for (auto& floor : m_connectedFloors)
		{
			std::vector<FloorDimensions> fD = floor->GetDimensions();
			for (FloorDimensions& dim : fD)
			{
				if (dim.checkCollision(v, checkV))
				{
					//in 2 dimesions
					//dir = a*direction + b*normal
					//b = (dirX-dirY*directionX)/(normalX*directionY + normalY*directionX)
					//b = dir part in normal direction
					float b = (dir.X - dir.Y * m_direction.X) / (m_normal.X * m_direction.Y + m_normal.Y * m_direction.X);
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
		SetSmall(DeltaTime);
	}
	else
	{
		SetBig(DeltaTime);
	}
}

void AWall::TickWallViewTypeSmall(float DeltaTime)
{
	SetSmall(DeltaTime);
}

void AWall::TickWallViewTypeBig(float DeltaTime)
{
	SetBig(DeltaTime);
}

void AWall::TickFloorViewTypeAll()
{
	SetActorHiddenInGame(false);
}

void AWall::TickFloorViewTypeOnly()
{
	GlobalSettings* settings = GlobalSettings::GetInstance();
	//todo only change when change is needed
	if (m_floorPosition == settings->GetFloorPosition().GetPosition())
	{
		SetActorHiddenInGame(false);
	}
	else
	{
		SetActorHiddenInGame(true);
	}
}

void AWall::TickFloorViewTypeAllBelow()
{
	GlobalSettings* settings = GlobalSettings::GetInstance();
	//todo only change when change is needed
	if (m_floorPosition <= settings->GetFloorPosition().GetPosition())
	{
		SetActorHiddenInGame(false);
	}
	else
	{
		SetActorHiddenInGame(true);
	}
}

