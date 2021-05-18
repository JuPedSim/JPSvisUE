// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"
#include "Floor.h"
#include "../Data/Line.h"
#include "FloorStructure.h"
#include "../../Settings/GlobalSettings.h"

#include "../../DataManagment/Cache/CacheEntry.h"
#include "Pedestrian.h"
#include "../../RuntimeControl/FloorPosition.h"
#include "../../RuntimeControl/FramePosition.h"
#include "../../RuntimeControl/AutoPlaySpeed.h"
#include "../../DataManagment/FileReaders/StructureFile/StructureFileReader.h"

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
	settings->SetTimePerFrame(m_cache.GetFileReader().get()->GetTimePerFrame());
	int lastPos = settings->GetFramePosition().get()->GetPosition();
	std::shared_ptr<FramePosition> framePosition = std::make_shared<FramePosition>(m_cache.GetFramesCount(), settings->GetTimePerFrame());
	framePosition.get()->SetPositionWithClamp(lastPos);
	settings->SetFramePosition(framePosition);
	for (int i = 0; i < m_pedestrians.size(); i++)
	{
		m_pedestrians.at(i)->DestroyAll();
	}
	m_cacheIsSet = true;
}

void ABuilding::LoadStructure()
{
	GlobalSettings* settings = GlobalSettings::GetInstance();
	std::vector<FloorWithHeight> lines = StructureFileReader::LoadStructure(settings->GetStructureFilePath());

	m_floors = SpawnItems<AFloorStructure>(lines.size(), m_floorStructureClass);
	for (int i = 0; i < lines.size(); i++)
	{
		m_floors.at(i)->Init(*lines.at(i).lines.get(), i);
	}
	std::vector<float> floorHeights = std::vector<float>();
	floorHeights.resize(lines.size());
	for (int i = 0; i < lines.size(); i++)
	{
		floorHeights.at(i) = lines.at(i).height;
	}
	settings->SetFloorHeights(floorHeights);

	int lastFloorPosition = settings->GetFloorPosition().get()->GetPosition();
	std::shared_ptr<FloorPosition> floorPosition = std::make_shared<FloorPosition>(lines.size());
	floorPosition.get()->SetPositionWithClamp(lastFloorPosition);
	settings->SetFloorPosition(floorPosition);
}

void ABuilding::MovePedestrians()
{
	if (m_cacheIsSet)
	{
		GlobalSettings* settings = GlobalSettings::GetInstance();
		int pos = settings->GetFramePosition().get()->GetPosition();
		//pre load forward
		for (int i = settings->GetPreFetchCacheForward(); i >= 1; i--)
		{
			if (settings->GetFramePosition().get()->CheckPositionValid(pos + i))
			{
				m_cache.LoadCacheEntryAsync(pos + i);
			}
		}
		//pre load backward
		for (int i = settings->GetPreFetchCacheBackward(); i >= 1; i--)
		{
			if (settings->GetFramePosition().get()->CheckPositionValid(pos - i))
			{
				m_cache.LoadCacheEntryAsync(pos - i);
			}
		}

		float time = (float)pos * settings->GetTimePerFrame();

		//load needed value
		CacheEntry entry = m_cache.LoadCacheEntrySync(pos);
		std::vector<Person> persons = entry.GetPersons();
		std::vector<Person> toCreate;
		//toDelete
		for (int i = 0;i< m_pedestrians.size();i++)
		{
			bool found = false;
			for (int n = 0;n< persons.size();n++)
			{
				if (persons.at(n).id==m_pedestrians.at(i)->GetID()) 
				{
					found = true;
					break;
				}
			}
			if (!found) 
			{
				m_pedestrians.at(i)->DestroyAll();
				m_pedestrians.erase(m_pedestrians.begin()+i);
				i--;
			}
		}
		//toCreate
		for (int n = 0;n<persons.size();n++) 
		{
			bool found = false;
			for (int i = 0; i < m_pedestrians.size(); i++)
			{
				if (persons.at(n).id == m_pedestrians.at(i)->GetID())
				{
					found = true;
					break;
				}
			}
			if (!found)
			{
				toCreate.push_back(persons.at(n));
			}
		}
		//sync
		for (int i = 0; i < m_pedestrians.size(); i++)
		{
			for (int n = 0; n < persons.size(); n++)
			{
				Person person = persons.at(n);
				if (person.id == m_pedestrians.at(i)->GetID())
				{
					if (GetShouldBeHidden(person.z))
					{
						m_pedestrians.at(i)->SetActorHiddenInGame(true);
					}
					else
					{
						m_pedestrians.at(i)->SetActorHiddenInGame(false);
					}
					m_pedestrians.at(i)->SetPosition(person, time);
					break;
				}
			}
		}
		//create
		for (int i = 0; i < toCreate.size(); i++)
		{
			Person person = toCreate.at(i);
			APedestrian* pedestrian = SpawnItem<APedestrian>(m_pedestrianClass);
			pedestrian->InitVariables(person.id,time);
			pedestrian->SetPosition(person, time);
			if (GetShouldBeHidden(person.z))
			{
				pedestrian->SetVisible();
			}
			m_pedestrians.push_back(pedestrian);
		}
	}
}

bool ABuilding::GetShouldBeHidden(float height)
{
	GlobalSettings* settings = GlobalSettings::GetInstance();
	float minDis = FLT_MAX;
	int pos = 0;
	for (int i = 0; i < settings->GetFloorHeights().size(); i++)
	{
		float distance = std::abs(settings->GetFloorHeights().at(i) - height);
		if (distance < minDis)
		{
			minDis = distance;
			pos = i;
		}
	}

	int currentFloor = settings->GetFloorPosition().get()->GetPosition();
	switch (GlobalSettings::GetInstance()->GetFloorViewType())
	{
	case FloorViewType::ALL_BELOW_VIEW:
		if (pos <= currentFloor)
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
