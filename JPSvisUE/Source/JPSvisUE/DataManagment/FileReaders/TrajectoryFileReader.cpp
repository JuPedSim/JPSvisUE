// Fill out your copyright notice in the Description page of Project Settings.


#include "TrajectoryFileReader.h"
#include "../Cache/CacheLine.h"
#include "../Cache/CacheEntry.h"

#include <chrono>
#include <thread>

TrajectoryFileReader::TrajectoryFileReader()
{
}

TrajectoryFileReader::~TrajectoryFileReader()
{
}
CacheLine TrajectoryFileReader::LoadCacheLine(int startAddress, int count, std::string filePath, int tag, unsigned int lruID)
{
	//std::this_thread::sleep_for(std::chrono::milliseconds(1000)); to test cache
	switch (GetDataType(filePath))
	{
	case DataType::BIN:
		return TrajectoryFileReader::CacheLineConstractor(TrajectoryFileReader::LoadCacheLineBin(startAddress, count, filePath), tag, lruID);
	case DataType::TXT:
		return TrajectoryFileReader::CacheLineConstractor(TrajectoryFileReader::LoadCacheLineTxt(startAddress, count, filePath), tag, lruID);
	case DataType::NONE:
		throw std::invalid_argument("Unsuported File Format");
	default:
		throw std::invalid_argument("Unsuported File Format");
	}

}

int TrajectoryFileReader::GetFrames(std::string filePath)
{
	switch (GetDataType(filePath))
	{
	case DataType::BIN:
		return TrajectoryFileReader::GetFramesBin(filePath);
	case DataType::TXT:
		return TrajectoryFileReader::GetFramesTxt(filePath);
	case DataType::NONE:
		throw std::invalid_argument("Unsuported File Format");
	default:
		throw std::invalid_argument("Unsuported File Format");
	}
}

CacheLine TrajectoryFileReader::CacheLineConstractor(std::vector<CacheEntry> entries, int tag, unsigned int lruID)
{
	return CacheLine(tag, entries, lruID);
}

std::vector<CacheEntry> TrajectoryFileReader::LoadCacheLineBin(int startAddress, int count, std::string filePath)
{
	std::ifstream is;
	is.open(filePath, std::ios::binary);
	if (is.fail())
	{
		throw std::invalid_argument("File not found");
	}


	int32 framesCount;
	is.read(reinterpret_cast<char*>(&framesCount), sizeof(framesCount));
	int32 perframeCount;
	is.read(reinterpret_cast<char*>(&perframeCount), sizeof(perframeCount));


	int byteOffset = 2 * sizeof(int32) + startAddress * sizeof(float) * 4 * perframeCount;

	std::vector<CacheEntry> entries;
	entries.resize(count);

	is.seekg(std::streampos(byteOffset));
	for (int i = 0; i < count; i++)
	{
		std::vector<Person> persons;
		persons.resize(perframeCount);
		for (int n = 0; n < perframeCount; n++)
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
	return entries;
}

std::vector<CacheEntry> TrajectoryFileReader::LoadCacheLineTxt(int startAddress, int count, std::string filePath)
{
	std::vector<CacheEntry> entries;
	return entries;
}

int TrajectoryFileReader::GetFramesBin(std::string filePath)
{
	std::ifstream is;
	is.open(filePath, std::ios::binary);

	int32 framesCount;
	is.read(reinterpret_cast<char*>(&framesCount), sizeof(framesCount));

	return framesCount;
}

int TrajectoryFileReader::GetFramesTxt(std::string filePath)
{
	return 0;
}

DataType TrajectoryFileReader::GetDataType(std::string filePath)
{
	std::string dataTypeReversed = "";
	for (int i = filePath.size() - 1; i >= 0; i--)
	{
		if (filePath.at(i) != '.')
		{
			dataTypeReversed.push_back(filePath.at(i));
		}
		else
		{
			break;
		}
	}
	std::string dataType = "";
	for (int i = dataTypeReversed.size() - 1; i >= 0; i--)
	{
		dataType.push_back(dataTypeReversed.at(i));
	}
	if (dataType == "txt")
	{
		return DataType::TXT;
	}
	else if (dataType == "bin")
	{
		return DataType::BIN;
	}
	else
	{
		return DataType::NONE;
	}
}
