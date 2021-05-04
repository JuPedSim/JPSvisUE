// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <vector>
#include <string>
#include <memory>

class Line;
/**
 *
 */
struct FloorWithHeight {
	float height;
	std::shared_ptr<std::vector<Line>> lines;
};
class JPSVISUE_API StructureFileReader
{
public:
	StructureFileReader();
	~StructureFileReader();
	static std::vector<FloorWithHeight> LoadStructure(std::string filePath);
private:
	bool compare(Line l1, Line l2);
};
