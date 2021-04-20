// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <fstream>
#include <string>
#include <vector>

/**
 * 
 */
class JPSVISUE_API FileReaderHelper
{
public:
	FileReaderHelper();
	~FileReaderHelper();
	static long SeekLineSave(std::ifstream& is, long pos, long size);
	static long GetSize(std::string path);
	static std::vector<std::string> GetValuesInLine(std::string line,std::vector<int> positons);
private:
	static long SeekPosSave(std::ifstream& is, long pos, long size);
	static long GetPositionBeforeNewLineIfNeeded(std::ifstream& is, long pos, long size);
	
};
