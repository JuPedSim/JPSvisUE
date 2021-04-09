// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"
// Sets default values
ABuilding::ABuilding()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_cacheIsSet = false;
}

// Called when the game starts or when spawned
void ABuilding::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GlobalSettings* settings = GlobalSettings::GetInstance();
	if (settings->GetStructureFileChanged())
	{
		LoadStructure();
	}
	
	if (settings->GetTrajectoryFileChanged())
	{
		LoadPedestrians();
	}

	SetAutoPlayFrame(DeltaTime);
	MovePedestrians();
}

void ABuilding::DestroyAll(bool bNetForce, bool bShouldModifyLevel)
{
	for (int i = 0; i < m_pedestrians.size(); i++)
	{
		m_pedestrians.at(i)->DestroyAll(bNetForce, bShouldModifyLevel);
	}
	for (int i = 0; i < m_floors.size(); i++)
	{
		m_floors.at(i)->DestroyAll(bNetForce, bShouldModifyLevel);
	}
	Destroy(bNetForce, bShouldModifyLevel);
}

void ABuilding::SetAutoPlayFrame(float delta)
{
	GlobalSettings* settings = GlobalSettings::GetInstance();
	if (settings->GetIsAutoPlay()) 
	{
		delta = delta * settings->GetAutoPlaySpeed().get()->GetSpeedUpFactor();
		settings->GetFramePosition().get()->TimeSensitiveChange(delta);
	}
}

void ABuilding::LoadPedestrians()
{
	GlobalSettings* settings = GlobalSettings::GetInstance();
	m_cache = Cache(settings->GetCacheBitsAssociativeness(), settings->GetCacheBitsIndex(), settings->GetCacheBitsWordOffset(), settings->GetTrajectoryFilePath());
	int lastPos = settings->GetFramePosition().get()->GetPosition();
	std::shared_ptr<FramePosition> framePosition = std::make_shared<FramePosition>(m_cache.GetFramesCount(), settings->GetTimePerFrame());
	framePosition.get()->SetPositionWithClamp(lastPos);
	settings->SetFramePosition(framePosition);
	CacheEntry firstEntry = m_cache.GetCacheEntry(0);

	for (int i = 0; i < m_pedestrians.size(); i++)
	{
		m_pedestrians.at(i)->DestroyAll();
	}

	m_pedestrians = SpawnItems<APedestrian>(firstEntry.GetPersons().size(), m_pedestrianClass);
	for (int i = 0; i < m_pedestrians.size(); i++)
	{
		Person person = firstEntry.GetPersons().at(i);
		m_pedestrians.at(i)->InitVariables(person.id);
		m_pedestrians.at(i)->SetPosition(FVector(person.x, person.y, person.z));
		m_pedestrians.at(i)->SetVisible();
	}
	m_cacheIsSet = true;
}

void ABuilding::LoadStructure()
{
	GlobalSettings* settings = GlobalSettings::GetInstance();


	float h1 = 20;
	float h2 = 40;

	std::vector<float> floorHeights = std::vector<float>();
	floorHeights.resize(3);
	floorHeights.at(0) = 0;
	floorHeights.at(1) = h1;
	floorHeights.at(2) = h2;

	settings->SetFloorHeights(floorHeights);

	std::vector<Line> lines1 = std::vector<Line>();
	lines1.resize(7);
	lines1.at(0) = Line(FVector(-10, -10, 0.f), FVector(-10, 70, 0.f));
	lines1.at(1) = Line(FVector(-10, 70, 0.f), FVector(30, 70, 0.f));
	lines1.at(2) = Line(FVector(30, 70, 0.f), FVector(30, 50, 0.f));
	lines1.at(3) = Line(FVector(30, 50, 0.f), FVector(60, 50, 0.f));
	lines1.at(4) = Line(FVector(60, 50, 0.f), FVector(60, -10, 0.f));
	lines1.at(5) = Line(FVector(60, -10, 0.f), FVector(-10, -10, 0.f));
	lines1.at(6) = Line(FVector(30, -10, 0.f), FVector(30, 20, 0.f));

	std::vector<Line> lines2 = std::vector<Line>();
	lines2.resize(7);
	lines2.at(0) = Line(FVector(-10, -10, h1), FVector(-10, 70, h1));
	lines2.at(1) = Line(FVector(-10, 70, h1), FVector(30, 70, h1));
	lines2.at(2) = Line(FVector(30, 70, h1), FVector(30, 50, h1));
	lines2.at(3) = Line(FVector(30, 50, h1), FVector(60, 50, h1));
	lines2.at(4) = Line(FVector(60, 50, h1), FVector(60, -10, h1));
	lines2.at(5) = Line(FVector(60, -10, h1), FVector(-10, -10, h1));
	lines2.at(6) = Line(FVector(30, -10, h1), FVector(30, 20, h1));

	std::vector<Line> lines3 = std::vector<Line>();
	lines3.resize(7);
	lines3.at(0) = Line(FVector(-10, -10, h2), FVector(-10, 70, h2));
	lines3.at(1) = Line(FVector(-10, 70, h2), FVector(30, 70, h2));
	lines3.at(2) = Line(FVector(30, 70, h2), FVector(30, 50, h2));
	lines3.at(3) = Line(FVector(30, 50, h2), FVector(60, 50, h2));
	lines3.at(4) = Line(FVector(60, 50, h2), FVector(60, -10, h2));
	lines3.at(5) = Line(FVector(60, -10, h2), FVector(-10, -10, h2));
	lines3.at(6) = Line(FVector(30, -10, h2), FVector(30, 20, h2));

	for (int i = 0; i < m_floors.size(); i++)
	{
		m_floors.at(i)->DestroyAll();
	}

	m_floors = SpawnItems<AFloorStructure>(3, m_floorStructureClass);
	m_floors.at(0)->Init(lines1, 0);
	m_floors.at(1)->Init(lines2, 1);
	m_floors.at(2)->Init(lines3, 2);

	int lastFloorPosition = settings->GetFloorPosition().get()->GetPosition();
	std::shared_ptr<FloorPosition> floorPosition = std::make_shared<FloorPosition>(3);
	floorPosition.get()->SetPositionWithClamp(lastFloorPosition);
	settings->SetFloorPosition(floorPosition);
}

void ABuilding::MovePedestrians()
{
	if (m_cacheIsSet) 
	{
		GlobalSettings* settings = GlobalSettings::GetInstance();
		/*if (settings->GetFramePosition().GetPositionWasChanged())
		{*/
		CacheEntry entry = m_cache.GetCacheEntry(settings->GetFramePosition().get()->GetPosition());
		for (int i = 0; i < m_pedestrians.size(); i++)
		{
			Person person = entry.GetPersons().at(i);
			if (GetShouldBeHidden(person.z))
			{
				m_pedestrians.at(i)->SetActorHiddenInGame(true);
			}
			else
			{
				m_pedestrians.at(i)->SetActorHiddenInGame(false);
			}
			m_pedestrians.at(i)->SetPosition(FVector(person.x, person.y, person.z));
		}
		//}
	}
}

bool ABuilding::GetShouldBeHidden(float height)
{
	GlobalSettings* settings = GlobalSettings::GetInstance();
	float minDis = FLT_MAX;
	int pos = 0;
	for (int i = 0;i<settings->GetFloorHeights().size();i++) 
	{
		float distance = std::abs(settings->GetFloorHeights().at(i) - height);
		if (distance<minDis) 
		{
			minDis = distance;
			pos = i;
		}
	}

	int currentFloor = settings->GetFloorPosition().get()->GetPosition();
	switch (GlobalSettings::GetInstance()->GetFloorViewType())
	{
	case FloorViewType::ALL_BELOW_VIEW:
		if (pos<=currentFloor) 
		{
			return false;
		}
		break;
	case FloorViewType::ALL_VIEW:
		return false;
		break;
	case FloorViewType::ONLY_VIEW:
		if (pos == currentFloor)
		{
			return false;
		}
		break;
	default:
		break;
	}
	return true;
}
