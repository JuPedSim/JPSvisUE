// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Developer/DesktopPlatform/Public/IDesktopPlatform.h"
#include "Developer/DesktopPlatform/Public/DesktopPlatformModule.h"
#include "CoreMinimal.h"

/**
 *
 */
class JPSVISUE_API FileOpener
{
public:
	FileOpener();
	~FileOpener();
	/*
	 * Opens a file dialog for the specified data. Leave FileTypes empty to be able to select any files.
	 * Filetypes must be in the format of: <File type Description>|*.<actual extension>
	 * You can combine multiple extensions by placing ";" between them
	 * For example: Text Files|*.txt|Excel files|*.csv|Image Files|*.png;*.jpg;*.bmp will display 3 lines for 3 different type of files.
	 * credits: https://www.orfeasel.com/creating-a-file-picker/
	 */
	static FString OpenFileDialogSingleSelect(const FString& DialogTitle, const FString& DefaultPath, const FString& FileTypes);
	static TArray<FString> OpenFileDialogMultiSelect(const FString& DialogTitle, const FString& DefaultPath, const FString& FileTypes);
private:
	//Selection Flag: A value of 0 represents single file selection while a value of 1 represents multiple file selection
	static TArray<FString> OpenFileDialog(const FString& DialogTitle, const FString& DefaultPath, const FString& FileTypes, uint32 SelectionFlag);
};
