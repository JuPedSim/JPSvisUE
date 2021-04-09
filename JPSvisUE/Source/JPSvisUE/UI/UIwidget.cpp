// Fill out your copyright notice in the Description page of Project Settings.


#include "UIwidget.h"


void UUIwidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	m_wallViewTypeButtonSmall->OnClicked.AddUniqueDynamic(this, &UUIwidget::SetWallViewTypeSmall);
	m_wallViewTypeButtonLarge->OnClicked.AddUniqueDynamic(this, &UUIwidget::SetWallViewTypeLarge);
	m_wallViewTypeButtonDynamic->OnClicked.AddUniqueDynamic(this, &UUIwidget::SetWallViewTypeDynamic);
	m_floorViewTypeButtonAll->OnClicked.AddUniqueDynamic(this, &UUIwidget::SetFloorViewTypeAll);
	m_floorViewTypeButtonAllBelow->OnClicked.AddUniqueDynamic(this, &UUIwidget::SetFloorViewTypeAllBelow);
	m_floorViewTypeButtonOnly->OnClicked.AddUniqueDynamic(this, &UUIwidget::SetFloorViewTypeOnly);
	m_frameForwardButton->OnClicked.AddUniqueDynamic(this, &UUIwidget::SetFramesForward);
	m_frameBackwardButton->OnClicked.AddUniqueDynamic(this, &UUIwidget::SetFramesBackward);
	m_framePlayButton->OnClicked.AddUniqueDynamic(this, &UUIwidget::PlayFrames);
	m_framePauseButton->OnClicked.AddUniqueDynamic(this, &UUIwidget::PauseFrames);
	m_speedIncreaseButton->OnClicked.AddUniqueDynamic(this, &UUIwidget::IncreaseSpeed);
	m_speedDecreaseButton->OnClicked.AddUniqueDynamic(this, &UUIwidget::DecreaseSpeed);
	m_floorUpButton->OnClicked.AddUniqueDynamic(this, &UUIwidget::IncreaseFloorPosition);
	m_floorDownButton->OnClicked.AddUniqueDynamic(this, &UUIwidget::DecreaseFloorPosition);
	m_openTrajectoryFileButton->OnClicked.AddUniqueDynamic(this, &UUIwidget::OpenTrajectoryFile);
	m_openStructureFileButton->OnClicked.AddUniqueDynamic(this, &UUIwidget::OpenStructureFile);

	GlobalSettings* settings = GlobalSettings::GetInstance();
	std::shared_ptr<UUserWidget> uiPointer(this);
	settings->SetUI(uiPointer);
}

void UUIwidget::SetWallViewTypeLarge()
{
	GlobalSettings* settings = GlobalSettings::GetInstance();
	settings->SetWallViewType(WallViewType::LARGE_VIEW);
}

void UUIwidget::SetWallViewTypeSmall()
{
	GlobalSettings* settings = GlobalSettings::GetInstance();
	settings->SetWallViewType(WallViewType::SMALL_VIEW);
}

void UUIwidget::SetWallViewTypeDynamic()
{
	GlobalSettings* settings = GlobalSettings::GetInstance();
	settings->SetWallViewType(WallViewType::DYNAMIC_VIEW);
}

void UUIwidget::SetFloorViewTypeOnly()
{
	GlobalSettings* settings = GlobalSettings::GetInstance();
	settings->SetFloorViewType(FloorViewType::ONLY_VIEW);
}

void UUIwidget::SetFloorViewTypeAll()
{
	GlobalSettings* settings = GlobalSettings::GetInstance();
	settings->SetFloorViewType(FloorViewType::ALL_VIEW);
}

void UUIwidget::SetFloorViewTypeAllBelow()
{
	GlobalSettings* settings = GlobalSettings::GetInstance();
	settings->SetFloorViewType(FloorViewType::ALL_BELOW_VIEW);
}

void UUIwidget::SetFramesForward()
{
	GlobalSettings* settings = GlobalSettings::GetInstance();
	settings->GetFramePosition().get()->Increase();
}

void UUIwidget::SetFramesBackward()
{
	GlobalSettings* settings = GlobalSettings::GetInstance();
	settings->GetFramePosition().get()->Decrease();
}

void UUIwidget::PlayFrames()
{
	GlobalSettings* settings = GlobalSettings::GetInstance();
	settings->SetIsAutoPlay(true);
}

void UUIwidget::PauseFrames()
{
	GlobalSettings* settings = GlobalSettings::GetInstance();
	settings->SetIsAutoPlay(false);
}

void UUIwidget::IncreaseSpeed()
{
	GlobalSettings* settings = GlobalSettings::GetInstance();
	settings->GetAutoPlaySpeed().get()->Increase();
}

void UUIwidget::DecreaseSpeed()
{
	GlobalSettings* settings = GlobalSettings::GetInstance();
	settings->GetAutoPlaySpeed().get()->Decrease();
}

void UUIwidget::IncreaseFloorPosition()
{
	GlobalSettings* settings = GlobalSettings::GetInstance();
	settings->GetFloorPosition().get()->Increase();
}

void UUIwidget::DecreaseFloorPosition()
{
	GlobalSettings* settings = GlobalSettings::GetInstance();
	settings->GetFloorPosition().get()->Decrease();
}

void UUIwidget::OpenTrajectoryFile()
{
	GlobalSettings* settings = GlobalSettings::GetInstance();
	FString fileName = FileOpener::OpenFileDialogSingleSelect("Trajectory Files", "", "Trajectory File|*.bin");
	if (!fileName.IsEmpty()) 
	{
		settings->SetTrajectoryFilePath(std::string(TCHAR_TO_UTF8(*fileName)));
	}
}
void UUIwidget::OpenStructureFile()
{
	GlobalSettings* settings = GlobalSettings::GetInstance();
	FString fileName = FileOpener::OpenFileDialogSingleSelect("Structure Files", "", "Structure File|*.dxf");
	if (!fileName.IsEmpty())
	{
		settings->SetStructureFilePath(std::string(TCHAR_TO_UTF8(*fileName)));
	}
}

