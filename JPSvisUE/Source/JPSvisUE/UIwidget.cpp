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
	int pos = settings->GetCurrentFrame() + 1;
	if (pos >= settings->GetFramesCount())
	{
		pos = settings->GetFramesCount()-1;
	}
	settings->SetCurrentFrame(pos);
}

void UUIwidget::SetFramesBackward()
{
	GlobalSettings* settings = GlobalSettings::GetInstance();
	int pos = settings->GetCurrentFrame() - 1;
	if (pos<0) 
	{
		pos = 0;
	}
	settings->SetCurrentFrame(pos);
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
