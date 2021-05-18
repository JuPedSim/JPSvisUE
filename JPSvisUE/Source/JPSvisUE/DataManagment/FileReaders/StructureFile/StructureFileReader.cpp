// Fill out your copyright notice in the Description page of Project Settings.


#include "StructureFileReader.h"
#include "../../../Structure/Data/Line.h"

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include "DXFfileReader.h"
//#include <libdxfrw.h>
//#include <libdwgr.h>
#include <algorithm>

StructureFileReader::StructureFileReader()
{
}

StructureFileReader::~StructureFileReader()
{
}

std::vector<FloorWithHeight> StructureFileReader::LoadStructure(std::string filePath)
{
	//DXFfileReader* dxffileReader = new DXFfileReader();

	//dxfRW* dxf = new dxfRW(filePath.c_str());

	bool success = true;//dxf->read(dxffileReader, false);



	if (success)
	{
		//temp
		std::string line;
		std::vector<Line> lines;
		std::ifstream stream(filePath);
		while (getline(stream,line))
		{
			if (line.size()>=11) 
			{
				std::string arr[6];
				std::string temp = "";
				int m = 0;
				for (int i = 0;i<line.size();i++) 
				{
					if (line[i]==';') 
					{
						arr[m] = temp;
						temp = "";
						m++;
					}
					else
					{
						temp += line[i];
					}
				}
				arr[m] = temp;

				float x1 = std::stof(arr[0]);
				float y1 = std::stof(arr[1]);
				float z1 = std::stof(arr[2]);
				float x2 = std::stof(arr[3]);
				float y2 = std::stof(arr[4]);
				float z2 = std::stof(arr[5]);
				lines.push_back(Line(FVector(x1,y1,z1), FVector(x2, y2, z2)));
			}
		}
		//end temp







		//std::vector<Line> lines = dxffileReader->GetLines();
		//std::sort(lines.begin(),lines.end(), StructureFileReader::compare);
	
		std::vector<std::shared_ptr<std::vector<Line>>> splited;

		float z = 0;
		bool first = true;
		for (int i = 0;i<lines.size();i++) 
		{
			if (first||lines.at(i).GetPoint1().Z!=z)
			{
				splited.push_back(std::make_shared<std::vector<Line>>());
				first = false;
			}
			splited.at(splited.size() - 1).get()->push_back(lines.at(i));
		}

		std::vector<FloorWithHeight> structure;
		structure.resize(splited.size());

		for (int i = 0;i< splited.size();i++)
		{
			FloorWithHeight f;
			f.height = splited.at(i).get()->at(0).GetPoint1().Y;
			f.lines = splited.at(i);
			structure.at(i) = f;
		}
		return structure;
	}
	else
	{
		throw std::exception("could not load file");
	}


	/*float h1 = 20;
	float h2 = 40;

	std::vector<float> floorHeights = std::vector<float>();
	floorHeights.resize(3);
	floorHeights.at(0) = 0;
	floorHeights.at(1) = h1;
	floorHeights.at(2) = h2;

	std::shared_ptr<std::vector<Line>> lines1 = std::make_shared<std::vector<Line>>();
	lines1.get()->resize(7);
	lines1.get()->at(0) = Line(FVector(-10, -10, 0.f), FVector(-10, 70, 0.f));
	lines1.get()->at(1) = Line(FVector(-10, 70, 0.f), FVector(30, 70, 0.f));
	lines1.get()->at(2) = Line(FVector(30, 70, 0.f), FVector(30, 50, 0.f));
	lines1.get()->at(3) = Line(FVector(30, 50, 0.f), FVector(60, 50, 0.f));
	lines1.get()->at(4) = Line(FVector(60, 50, 0.f), FVector(60, -10, 0.f));
	lines1.get()->at(5) = Line(FVector(60, -10, 0.f), FVector(-10, -10, 0.f));
	lines1.get()->at(6) = Line(FVector(30, -10, 0.f), FVector(30, 20, 0.f));

	std::shared_ptr<std::vector<Line>> lines2 = std::make_shared<std::vector<Line>>();
	lines2.get()->resize(7);
	lines2.get()->at(0) = Line(FVector(-10, -10, h1), FVector(-10, 70, h1));
	lines2.get()->at(1) = Line(FVector(-10, 70, h1), FVector(30, 70, h1));
	lines2.get()->at(2) = Line(FVector(30, 70, h1), FVector(30, 50, h1));
	lines2.get()->at(3) = Line(FVector(30, 50, h1), FVector(60, 50, h1));
	lines2.get()->at(4) = Line(FVector(60, 50, h1), FVector(60, -10, h1));
	lines2.get()->at(5) = Line(FVector(60, -10, h1), FVector(-10, -10, h1));
	lines2.get()->at(6) = Line(FVector(30, -10, h1), FVector(30, 20, h1));

	std::shared_ptr<std::vector<Line>> lines3 = std::make_shared<std::vector<Line>>();
	lines3.get()->resize(7);
	lines3.get()->at(0) = Line(FVector(-10, -10, h2), FVector(-10, 70, h2));
	lines3.get()->at(1) = Line(FVector(-10, 70, h2), FVector(30, 70, h2));
	lines3.get()->at(2) = Line(FVector(30, 70, h2), FVector(30, 50, h2));
	lines3.get()->at(3) = Line(FVector(30, 50, h2), FVector(60, 50, h2));
	lines3.get()->at(4) = Line(FVector(60, 50, h2), FVector(60, -10, h2));
	lines3.get()->at(5) = Line(FVector(60, -10, h2), FVector(-10, -10, h2));
	lines3.get()->at(6) = Line(FVector(30, -10, h2), FVector(30, 20, h2));

	FloorWithHeight f1;
	f1.height = floorHeights.at(0);
	f1.lines = lines1;

	FloorWithHeight f2;
	f2.height = floorHeights.at(1);
	f2.lines = lines2;

	FloorWithHeight f3;
	f3.height = floorHeights.at(2);
	f3.lines = lines3;

	std::vector<FloorWithHeight> structure;
	structure.resize(3);
	structure.at(0) = f1;
	structure.at(1) = f2;
	structure.at(2) = f3;

	return structure;*/
}

bool StructureFileReader::compare(Line l1, Line l2)
{
	return l1.GetPoint1().Z<l2.GetPoint1().Z;
}
