// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Runtime/UMG/Public/Components/ComboBoxString.h>
#include <Runtime/UMG/Public/Components/Button.h>
#include "../Settings/GlobalSettings.h"
#include "../DataManagment/FileOpener/FileOpener.h"
#include <Runtime/UMG/Public/Components/Slider.h>
#include <Runtime/UMG/Public/Components/TextBlock.h>
#include <sstream>
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
		UButton* m_wallViewTypeButtonLarge;
	UPROPERTY(meta = (BindWidget))
		UButton* m_wallViewTypeButtonSmall;
	UPROPERTY(meta = (BindWidget))
		UButton* m_wallViewTypeButtonDynamic;
	UPROPERTY(meta = (BindWidget))
		UButton* m_frameForwardButton;
	UPROPERTY(meta = (BindWidget))
		UButton* m_frameBackwardButton;
	UPROPERTY(meta = (BindWidget))
		UButton* m_framePlayButton;
	UPROPERTY(meta = (BindWidget))
		UButton* m_framePauseButton;
	UPROPERTY(meta = (BindWidget))
		UButton* m_speedIncreaseButton;
	UPROPERTY(meta = (BindWidget))
		UButton* m_speedDecreaseButton;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* m_speedTextBlock;
	UPROPERTY(meta = (BindWidget))
		UButton* m_floorUpButton;
	UPROPERTY(meta = (BindWidget))
		UButton* m_floorDownButton;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* m_floorTextBlock;
	UPROPERTY(meta = (BindWidget))
		UButton* m_floorViewTypeButtonAll;
	UPROPERTY(meta = (BindWidget))
		UButton* m_floorViewTypeButtonAllBelow;
	UPROPERTY(meta = (BindWidget))
		UButton* m_floorViewTypeButtonOnly;
	UPROPERTY(meta = (BindWidget))
		UButton* m_openTrajectoryFileButton;
	UPROPERTY(meta = (BindWidget))
		UButton* m_openStructureFileButton;
public:
	UPROPERTY(meta = (BindWidget))
		UTextBlock* m_frameTextBox;
	UPROPERTY(meta = (BindWidget))
		USlider* m_framePosSlider;
protected:

	UFUNCTION()
	void SetWallViewTypeLarge();
	UFUNCTION()
	void SetWallViewTypeSmall();
	UFUNCTION()
	void SetWallViewTypeDynamic();
	UFUNCTION()
	void SetFloorViewTypeOnly();
	UFUNCTION()
	void SetFloorViewTypeAll();
	UFUNCTION()
	void SetFloorViewTypeAllBelow();
	UFUNCTION()
	void SetFramesForward();
	UFUNCTION()
	void SetFramesBackward();
	UFUNCTION()
	void PlayFrames();
	UFUNCTION()
	void PauseFrames();
	UFUNCTION()
	void IncreaseSpeed();
	UFUNCTION()
	void DecreaseSpeed();
	void ShowSpeedInUI();
	UFUNCTION()
	void IncreaseFloorPosition();
	UFUNCTION()
	void DecreaseFloorPosition();
	void ShowFloorInUI();
	UFUNCTION()
	void OpenTrajectoryFile();
	UFUNCTION()
	void OpenStructureFile();

	void NativeConstruct() override;
};
