// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Runtime/UMG/Public/Components/ComboBoxString.h>
#include <Runtime/UMG/Public/Components/Button.h>
#include <JPSvisUE/GlobalSettings.h>
#include "UIwidget.generated.h"


/**
 * 
 */
UCLASS()
class JPSVISUE_API UUIwidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		UComboBoxString* m_viewTypeComboBox;
	UPROPERTY(meta = (BindWidget))
		UButton* m_viewTypeButtonLarge;
	UPROPERTY(meta = (BindWidget))
		UButton* m_viewTypeButtonSmall;
	UPROPERTY(meta = (BindWidget))
		UButton* m_viewTypeButtonDynamic;

	UFUNCTION()
	void SetViewType();
	UFUNCTION()
	void SetViewTypeLarge();
	UFUNCTION()
	void SetViewTypeSmall();
	UFUNCTION()
	void SetViewTypeDynamic();

	void NativeConstruct() override;
};
