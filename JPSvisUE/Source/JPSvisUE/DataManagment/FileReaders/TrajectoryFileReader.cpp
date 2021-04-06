// Fill out your copyright notice in the Description page of Project Settings.


#include "TrajectoryFileReader.h"

TrajectoryFileReader::TrajectoryFileReader()
{
}

TrajectoryFileReader::~TrajectoryFileReader()
{
}

CacheLine TrajectoryFileReader::LoadCacheLine(int startAddress, int count,std::string filePath, int tag,unsigned int lruID)
{
	std::ifstream is;
	is.open(filePath,std::ios::binary);
	if (is.fail()) 
	{
		throw std::invalid_argument("File not found");
	}


	int32 framesCount;
	is.read(reinterpret_cast<char*>(&framesCount), sizeof(framesCount));
	int32 perframeCount;
	is.read(reinterpret_cast<char*>(&perframeCount), sizeof(perframeCount));

	
	int byteOffset = 2 * sizeof(int32) + startAddress * sizeof(float) * 4* perframeCount;

	std::vector<CacheEntry> entries;
	entries.resize(count);

	is.seekg(std::streampos(byteOffset));
	for (int i = 0;i<count;i++)
	{
		std::vector<Person> persons;
		persons.resize(perframeCount);
		for (int n = 0;n<perframeCount;n++) 
		{
			int32 id;
			is.read(reinterpret_cast<char*>(&id), sizeof(id));
			float x;
			is.read(reinterpret_cast<char*>(&x), sizeof(x));
			float y;
			is.read(reinterpret_cast<char*>(&y), sizeof(y));
			float z;
			is.read(reinterpret_cast<char*>(&z), sizeof(z));
			Person p;
			p.id = id;
			p.x = x;
			p.y = y;
			p.z = z;
			persons.at(n) = p;
		}
		entries.at(i) = CacheEntry(persons);
	}


	CacheLine line = CacheLine(tag,entries, lruID);
	return line;
}

int TrajectoryFileReader::GetFrames(std::string filePath)
{
	std::ifstream is;
	is.open(filePath, std::ios::binary);

	int32 framesCount;
	is.read(reinterpret_cast<char*>(&framesCount), sizeof(framesCount));

	return framesCount;
}
