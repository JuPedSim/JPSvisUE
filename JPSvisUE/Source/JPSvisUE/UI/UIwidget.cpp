// Fill out your copyright notice in the Description page of Project Settings.


#include "UIwidget.h"


void UUIwidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	m_viewTypeButtonSmall->OnClicked.AddUniqueDynamic(this, &UUIwidget::SetViewTypeSmall);
	m_viewTypeButtonLarge->OnClicked.AddUniqueDynamic(this, &UUIwidget::SetViewTypeLarge);
	m_viewTypeButtonDynamic->OnClicked.AddUniqueDynamic(this, &UUIwidget::SetViewTypeDynamic);
	m_frameForwardButton->OnClicked.AddUniqueDynamic(this, &UUIwidget::SetFramesForward);
	m_frameBackwardButton->OnClicked.AddUniqueDynamic(this, &UUIwidget::SetFramesBackward);
	m_framePlayButton->OnClicked.AddUniqueDynamic(this, &UUIwidget::PlayFrames);
	m_framePauseButton->OnClicked.AddUniqueDynamic(this, &UUIwidget::PauseFrames);
	m_speedIncreaseButton->OnClicked.AddUniqueDynamic(this, &UUIwidget::IncreaseSpeed);
	m_speedDecreaseButton->OnClicked.AddUniqueDynamic(this, &UUIwidget::DecreaseSpeed);
	m_floorUpButton->OnClicked.AddUniqueDynamic(this, &UUIwidget::IncreaseFloorPosition);
	m_floorDownButton->OnClicked.AddUniqueDynamic(this, &UUIwidget::DecreaseFloorPosition);
}

void UUIwidget::SetViewTypeLarge()
{
	GlobalSettings* settings = GlobalSettings::GetInstance();
	settings->SetViewType(LARGE_VIEW);
}

void UUIwidget::SetViewTypeSmall()
{
	GlobalSettings* settings = GlobalSettings::GetInstance();
	settings->SetViewType(SMALL_VIEW);
}

void UUIwidget::SetViewTypeDynamic()
{
	GlobalSettings* settings = GlobalSettings::GetInstance();
	settings->SetViewType(DYNAMIC_VIEW);
}

void UUIwidget::SetFramesForward()
{
	GlobalSettings* settings = GlobalSettings::GetInstance();
	settings->GetFramePosition().Increase();
}

void UUIwidget::SetFramesBackward()
{
	GlobalSettings* settings = GlobalSettings::GetInstance();
	settings->GetFramePosition().Decrease();
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
	float speed = settings->GetSpeedUpFactor() + settings->GetSpeedUpFactorIncrementSize();
	settings->SetSpeedUpFactor(speed);
	ShowSpeedInUI();
}

void UUIwidget::DecreaseSpeed()
{
	GlobalSettings* settings = GlobalSettings::GetInstance();
	float speed = settings->GetSpeedUpFactor() - settings->GetSpeedUpFactorIncrementSize();
	settings->SetSpeedUpFactor(speed);
	ShowSpeedInUI();
}

void UUIwidget::ShowSpeedInUI()
{
	GlobalSettings* settings = GlobalSettings::GetInstance();
	std::stringstream ss;
	ss << "speed Factor: " << settings->GetSpeedUpFactor();
	std::string str = ss.str();
	FString layerName(str.c_str());
	m_speedTextBlock->SetText(FText::FromString(layerName));
}

void UUIwidget::IncreaseFloorPosition()
{
	GlobalSettings* settings = GlobalSettings::GetInstance();
	settings->GetFloorPosition().Increase();
}

void UUIwidget::DecreaseFloorPosition()
{
	GlobalSettings* settings = GlobalSettings::GetInstance();
	settings->GetFloorPosition().Decrease();
}
