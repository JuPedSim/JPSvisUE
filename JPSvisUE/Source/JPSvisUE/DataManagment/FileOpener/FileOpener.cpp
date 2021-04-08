// Fill out your copyright notice in the Description page of Project Settings.


#include "FileOpener.h"

FileOpener::FileOpener()
{
}

FileOpener::~FileOpener()
{
}

FString FileOpener::OpenFileDialogSingleSelect(const FString& DialogTitle, const FString& DefaultPath, const FString& FileTypes)
{
	TArray<FString> FileNames = FileOpener::OpenFileDialog(DialogTitle, DefaultPath, FileTypes,0);
	if (FileNames.Num()==1)
	{
		return FileNames[0];
	}
	else
	{
		return FString("");
	}
}

TArray<FString> FileOpener::OpenFileDialogMultiSelect(const FString& DialogTitle, const FString& DefaultPath, const FString& FileTypes)
{
	return FileOpener::OpenFileDialog(DialogTitle, DefaultPath, FileTypes, 1);
}

TArray<FString> FileOpener::OpenFileDialog(const FString& DialogTitle, const FString& DefaultPath, const FString& FileTypes,  uint32 SelectionFlag)
{
	TArray<FString> OutFileNames;
	if (GEngine)
	{
		if (GEngine->GameViewport)
		{
			void* ParentWindowHandle = GEngine->GameViewport->GetWindow()->GetNativeWindow()->GetOSWindowHandle();
			IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
			if (DesktopPlatform)
			{
				//Opening the file picker!
				 DesktopPlatform->OpenFileDialog(ParentWindowHandle, DialogTitle, DefaultPath, FString(""), FileTypes, SelectionFlag, OutFileNames);
			}
		}
	}
	return OutFileNames;
}
