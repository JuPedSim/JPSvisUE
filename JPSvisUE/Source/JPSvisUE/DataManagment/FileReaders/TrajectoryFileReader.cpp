// Fill out your copyright notice in the Description page of Project Settings.


#include "TrajectoryFileReader.h"
#include "../Cache/CacheLine.h"
#include "FileReaderHelper.h"
#include "../../Settings/GlobalSettings.h"

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
		return TrajectoryFileReader::CacheLineConstructor(TrajectoryFileReader::LoadCacheLineBin(startAddress, count, filePath), tag, lruID);
	case DataType::TXT:
		return TrajectoryFileReader::CacheLineConstructor(TrajectoryFileReader::LoadCacheLineTxt(startAddress, count, filePath), tag, lruID);
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

CacheLine TrajectoryFileReader::CacheLineConstructor(std::vector<CacheEntry> entries, int tag, unsigned int lruID)
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
	std::vector<std::vector<Person>> vec = TrajectoryFileReader::Search(filePath, startAddress,count);
	std::vector<CacheEntry> entries;
	entries.resize(count);
	for (int i = 0;i< count;i++)
	{
		entries.at(i) = CacheEntry(vec.at(i));
	}
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
	TrajectoryFileDataPositions positions;
	positions.id = 0;
	positions.frame = 1;
	positions.x = 2;
	positions.y = 3;
	positions.z = 4;
	
	std::ifstream is;
	is.open(filePath, std::ios_base::binary);
	if (is.fail())
	{
		throw std::invalid_argument("File not found");
	}
	long size = FileReaderHelper::GetSize(filePath);

	TrajectoryFileFrameBoundaries boundaries = TrajectoryFileReader::GetFrameBoundaries(is, size);
	TrajectoryFileFrameInfo info = TrajectoryFileReader::GetFrameInfoWithoutStartEndPos(is, boundaries.stopPos, size, positions);
	is.close();
	return info.frame+1;
}

TrajectoryFileFrameInfo TrajectoryFileReader::GetFrameInfoWithoutStartEndPos(std::ifstream& is, long pos, long size, TrajectoryFileDataPositions trajectoryFileDataPositions)
{
	std::vector<int> posFrameID;
	posFrameID.push_back(trajectoryFileDataPositions.frame);

	pos = FileReaderHelper::SeekLineSave(is, pos, size);
	while (true) 
	{
		std::string line;
		pos = is.tellg();
		if (!std::getline(is, line))
		{
			throw std::exception("frame id not found");
		}
		std::vector<std::string> frameId = FileReaderHelper::GetValuesInLine(line, posFrameID);
		if (frameId.size() == 1)
		{
			int frame = atoi(frameId.at(0).c_str());
			TrajectoryFileFrameInfo info;
			info.frame = frame;
			info.pos = pos;
			return info;
		}
	}

	throw std::exception("frame id not found");
}

TrajectoryFileFrameInfo TrajectoryFileReader::GetFrameInfoWithStartEndPos(std::ifstream& is, long size, TrajectoryFileFrameInfo frameInfo, TrajectoryFileDataPositions trajectoryFileDataPositions)
{
	std::vector<int> posFrameID;
	posFrameID.push_back(trajectoryFileDataPositions.frame);
	TrajectoryFileFrameInfo info = frameInfo;


	long pos = FileReaderHelper::SeekLineSave(is, frameInfo.pos, size);
	long lastpos = pos;
	std::string line;
	while (pos > 0)
	{
		pos = FileReaderHelper::SeekLineSave(is, pos, size);
		std::getline(is, line);
		if (line.size() > 0)
		{
			bool startFound = false;
			if (line.at(0) != '#')
			{
				std::vector<std::string> frameId = FileReaderHelper::GetValuesInLine(line, posFrameID);
				if (frameId.size()==1) 
				{
					int frame = atoi(frameId.at(0).c_str());
					if (frame!=info.frame) 
					{
						startFound = true;
					}
				}
			}
			else
			{
				startFound = true;
			}
			if (startFound)
			{
				info.startPos = lastpos;
				long posTemp = is.tellg();
				bool atEnd = !std::getline(is, line);
				std::vector<std::string> frameId = FileReaderHelper::GetValuesInLine(line, posFrameID);
				while (!atEnd)
				{
					if (frameId.size()==1) 
					{
						int frame = atoi(frameId.at(0).c_str());
						if (frame != info.frame)
						{
							break;
						}
						else
						{
							posTemp = is.tellg();
						}
					}
					
					atEnd = !std::getline(is, line);
					frameId = FileReaderHelper::GetValuesInLine(line, posFrameID);
				}
				info.endPos = posTemp;
				return info;
			}
			lastpos = pos;
		}
		pos = pos - 1;
	}
	info.startPos = lastpos;
	return info;
}

std::vector<Person> TrajectoryFileReader::ConvertFrameInfoToPersons(std::ifstream& is, long size, TrajectoryFileFrameInfo frameInfo, TrajectoryFileDataPositions positions)
{
	std::vector<int> posFrameID;
	posFrameID.push_back(positions.id);
	posFrameID.push_back(positions.x);
	posFrameID.push_back(positions.y);
	posFrameID.push_back(positions.z);
	

	std::vector<Person> persons;
	if (frameInfo.frame!=-1) 
	{
		long pos = FileReaderHelper::SeekPosSave(is, frameInfo.startPos, size);
		std::string line;
		bool run = (bool)std::getline(is, line);
		while (pos <= frameInfo.endPos && run)
		{
			std::vector<std::string> vec = FileReaderHelper::GetValuesInLine(line, posFrameID);
			if (vec.size() == 4)
			{
				Person person;
				person.id = atoi(vec.at(0).c_str());
				person.x = std::stof(vec.at(1).c_str());
				person.y = std::stof(vec.at(2).c_str());
				person.z = std::stof(vec.at(3).c_str());
				persons.push_back(person);
			}
			pos = is.tellg();
			run = (bool)std::getline(is, line);
		}
	}
	return persons;
}

std::vector<std::vector<Person>> TrajectoryFileReader::Search(std::string filePath, int frame,int count)
{
	TrajectoryFileDataPositions positions;
	positions.id = 0;
	positions.frame = 1;
	positions.x = 2;
	positions.y = 3;
	positions.z = 4;

	std::ifstream is;
	is.open(filePath, std::ios_base::binary);
	if (is.fail())
	{
		throw std::invalid_argument("File not found");
	}
	long size = FileReaderHelper::GetSize(filePath);

	TrajectoryFileFrameBoundaries boundaries = TrajectoryFileReader::GetFrameBoundaries(is, size);
	
	std::vector<std::vector<Person>> vec;
	
	for (int i = 0;i<count;i++)
	{
		vec.push_back(TrajectoryFileReader::ConvertFrameInfoToPersons(is,size, TrajectoryFileReader::SearchHelper(is, size, frame+i, boundaries, positions), positions));
	}
	
	is.close();
	return vec;
}

TrajectoryFileFrameInfo TrajectoryFileReader::SearchHelper(std::ifstream& is,int size,int frame, TrajectoryFileFrameBoundaries boundaries, TrajectoryFileDataPositions positions)
{
	GlobalSettings* settings = GlobalSettings::GetInstance();
	int pos = FMath::Clamp(settings->GetLastFileReaderPos(), boundaries.startPos, boundaries.stopPos);
	TrajectoryFileFrameInfo info1 = TrajectoryFileReader::GetFrameInfoWithoutStartEndPos(is, pos, size, positions);
	TrajectoryFileFrameInfo info2;
	if (info1.frame <= frame)
	{
		info2 = TrajectoryFileReader::SearchForward(is, frame, size, info1, positions, boundaries);
	}
	else
	{
		info2 = TrajectoryFileReader::SearchBackward(is, frame, size, info1, positions, boundaries);
	}

	if (info2.endPos >= 0)
	{
		settings->SetLastFileReaderPos(info2.endPos);
	}

	return info2;
}

TrajectoryFileFrameInfo TrajectoryFileReader::SearchForward(std::ifstream& is,int frame, long size, TrajectoryFileFrameInfo startInfo, TrajectoryFileDataPositions trajectoryFileDataPositions, TrajectoryFileFrameBoundaries boundaries)
{
	std::vector<int> posFrameID;
	posFrameID.push_back(trajectoryFileDataPositions.frame);

	int currentFrame = startInfo.frame;
	long pos = FileReaderHelper::SeekPosSave(is,startInfo.pos,size);
	std::string line;
	while (currentFrame<=frame)
	{
		bool endReached = !std::getline(is, line);
		std::vector<std::string> vec = FileReaderHelper::GetValuesInLine(line, posFrameID);
		if (vec.size()==1) 
		{
			currentFrame = atoi(vec.at(0).c_str());
		}
		if (currentFrame == frame) 
		{
			TrajectoryFileFrameInfo info;
			info.frame = currentFrame;
			info.pos = pos;
			return TrajectoryFileReader::GetFrameInfoWithStartEndPos(is, size, info, trajectoryFileDataPositions);

		}
		pos = is.tellg();
		if (endReached || pos>= boundaries.stopPos)
		{
			break;
		}
	}
	
	TrajectoryFileFrameInfo info;
	info.frame = -1;
	info.pos = -1;
	info.startPos = -1;
	info.endPos = -1;
	return info;
}

TrajectoryFileFrameInfo TrajectoryFileReader::SearchBackward(std::ifstream& is, int frame, long size, TrajectoryFileFrameInfo startInfo, TrajectoryFileDataPositions trajectoryFileDataPositions, TrajectoryFileFrameBoundaries boundaries)
{
	std::vector<int> posFrameID;
	posFrameID.push_back(trajectoryFileDataPositions.frame);

	int currentFrame = startInfo.frame;
	long pos = FileReaderHelper::SeekPosSave(is, startInfo.pos, size);
	std::string line;
	while (currentFrame >= frame)
	{
		pos = FileReaderHelper::SeekLineSave(is, pos, size);
		bool endReached = !std::getline(is, line);
		std::vector<std::string> vec = FileReaderHelper::GetValuesInLine(line, posFrameID);
		if (vec.size() == 1)
		{
			currentFrame = atoi(vec.at(0).c_str());
		}
		if (currentFrame == frame)
		{
			TrajectoryFileFrameInfo info;
			info.frame = currentFrame;
			info.pos = pos;
			return TrajectoryFileReader::GetFrameInfoWithStartEndPos(is,size,info, trajectoryFileDataPositions);

		}
		pos = pos - 1;
		if (endReached || pos <= boundaries.startPos)
		{
			break;
		}
	}

	TrajectoryFileFrameInfo info;
	info.frame = -1;
	info.pos = -1;
	info.startPos = -1;
	return info;
}

TrajectoryFileFrameBoundaries TrajectoryFileReader::GetFrameBoundaries(std::ifstream& is, long size)
{
	TrajectoryFileFrameBoundaries boundaries;

	FileReaderHelper::SeekLineSave(is, 0, size);

	bool beginingFound = false;
	bool endFound = false;

	long lastPos = 0;
	std::string line;
	while (std::getline(is, line))
	{
		if (line.size() > 0 && line.at(0) >= '0' && line.at(0) <= '9')
		{
			beginingFound = true;
			boundaries.startPos = lastPos;
			break;
		}
		lastPos = is.tellg();
	}

	long pos = size - 1;
	while (pos > 0)
	{
		pos = FileReaderHelper::SeekLineSave(is, pos, size);
		std::getline(is, line);
		if (line.size() > 0 && line.at(0) >= '0' && line.at(0) <= '9')
		{
			endFound = true;
			boundaries.stopPos = pos;
			break;
		}


		pos = pos - 1;
	}

	if (beginingFound && endFound)
	{
		return boundaries;
	}
	else
	{
		throw std::exception("file is not valid");
	}
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
