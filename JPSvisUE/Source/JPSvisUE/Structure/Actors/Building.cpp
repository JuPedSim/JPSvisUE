// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"
// Sets default values
ABuilding::ABuilding()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABuilding::BeginPlay()
{
	Super::BeginPlay();
	GlobalSettings* settings = GlobalSettings::GetInstance();
	m_cache = Cache(settings->GetCacheBitsAssociativeness(),settings->GetCacheBitsIndex(),settings->GetCacheBitsWordOffset(),settings->GetTrajectoryFilePath());
	settings->SetFramePosition(FramePosition(m_cache.GetFramesCount(),settings->GetTimePerFrame()));
	CacheEntry firstEntry = m_cache.GetCacheEntry(0);

	m_pedestrians = SpawnItems<APedestrian>(firstEntry.GetPersons().size(), m_pedestrianClass);
	for (int i = 0;i<m_pedestrians.size();i++)
	{
		Person person = firstEntry.GetPersons().at(i);
		m_pedestrians.at(i)->InitVariables(person.id);
		m_pedestrians.at(i)->SetPosition(FVector(person.x,person.y,person.z));
		m_pedestrians.at(i)->SetVisible();
	}

	float h1 = 20;
	float h2 = 40;

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

	m_floors = SpawnItems<AFloorStructure>(3, m_floorStructureClass);
	m_floors.at(0)->Init(lines1,0);
	m_floors.at(1)->Init(lines2,1);
	m_floors.at(2)->Init(lines3,2);

	settings->SetFloorPosition(FloorPosition(3));
}

// Called every frame
void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	SetAutoPlayFrame(DeltaTime);

	MovePedestrians();
}

void ABuilding::SetAutoPlayFrame(float delta)
{
	GlobalSettings* settings = GlobalSettings::GetInstance();
	if (settings->GetIsAutoPlay()) 
	{
		delta = delta * settings->GetSpeedUpFactor();
		settings->GetFramePosition().TimeSensitiveChange(delta);
	}
}

void ABuilding::MovePedestrians()
{
	GlobalSettings* settings = GlobalSettings::GetInstance();
	if (settings->GetFramePosition().GetPositionWasChanged())
	{
		CacheEntry firstEntry = m_cache.GetCacheEntry(settings->GetFramePosition().GetPosition());
		for (int i = 0; i < m_pedestrians.size(); i++)
		{
			Person person = firstEntry.GetPersons().at(i);
			m_pedestrians.at(i)->SetPosition(FVector(person.x, person.y, person.z));
		}
	}
}
