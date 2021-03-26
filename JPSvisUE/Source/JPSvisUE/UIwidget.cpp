// Fill out your copyright notice in the Description page of Project Settings.


#include "UIwidget.h"
#include <sstream>



void UUIwidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetViewType();

	m_viewTypeButtonSmall->OnClicked.AddUniqueDynamic(this, &UUIwidget::SetViewTypeSmall);
	m_viewTypeButtonLarge->OnClicked.AddUniqueDynamic(this, &UUIwidget::SetViewTypeLarge);
	m_viewTypeButtonDynamic->OnClicked.AddUniqueDynamic(this, &UUIwidget::SetViewTypeDynamic);

	//this->viewTypeComboBox->OnSelectionChanged.AddUniqueDynamic(this, &UUIwidget::SetViewType);
}

void UUIwidget::SetViewType()
{
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
