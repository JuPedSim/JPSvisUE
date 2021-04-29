// Fill out your copyright notice in the Description page of Project Settings.

#include "TrajectoryFileReaderTXT.h"
#include "../../Cache/CacheLine.h"
#include "../FileReaderHelper.h"
#include "../../../Settings/GlobalSettings.h"

TrajectoryFileReaderTXT::TrajectoryFileReaderTXT(std::string filePath) : TrajectoryFileReader(filePath)
{
	SetTrajectoryFileDataPositions();
	SetFrameBoundaries();
	SetFramesCount();
	SetTimePerFrame();
}
TrajectoryFileReaderTXT::TrajectoryFileReaderTXT() : TrajectoryFileReader()
{
}

TrajectoryFileReaderTXT::~TrajectoryFileReaderTXT()
{
}
void TrajectoryFileReaderTXT::SetFramesCount()
{
	std::ifstream is;
	is.open(m_filePath, std::ios_base::binary);
	if (is.fail())
	{
		throw std::invalid_argument("File not found");
	}
	TrajectoryFileFrameInfo info = GetFrameInfoWithoutStartEndPos(is, m_boundaries.stopPos);
	is.close();

	m_framesCount = info.frame + 1;
}
void TrajectoryFileReaderTXT::SetTimePerFrame()
{
	std::ifstream is;
	is.open(m_filePath, std::ios_base::binary);
	if (is.fail())
	{
		throw std::invalid_argument("File not found");
	}
	std::string line;
	std::string comp = "#framerate: ";
	while (std::getline(is, line))
	{
		if (line.size() > 0 && line.at(0) == '#')
		{
			bool found = true;
			for (int i = 0; i < comp.size(); i++)
			{
				if (line.at(i) != comp.at(i))
				{
					found = false;
					break;
				}
			}
			if (found)
			{
				std::string number = "";
				for (int i = comp.size(); i < line.size(); i++)
				{
					number += line.at(i);
				}
				m_timePerFrame = 1.0f / std::stof(number.c_str());
				is.close();
				return;
			}
		}
	}
	is.close();

	m_timePerFrame = 1.f;
}
CacheLine TrajectoryFileReaderTXT::LoadCacheLine(int startAddress, int count, int tag, unsigned int lruID)
{
	std::vector<std::vector<Person>> vec = TrajectoryFileReaderTXT::Search(startAddress,count);
	std::vector<CacheEntry> entries;
	entries.resize(count);
	for (int i = 0;i< count;i++)
	{
		entries.at(i) = CacheEntry(vec.at(i));
	}
	return CacheLine(tag, entries, lruID);
}

TrajectoryFileFrameInfo TrajectoryFileReaderTXT::GetFrameInfoWithoutStartEndPos(std::ifstream& is, long pos)
{
	std::vector<int> posFrameID;
	posFrameID.push_back(m_positions.frame);

	pos = FileReaderHelper::SeekLineSave(is, pos, m_fileSize);
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

TrajectoryFileFrameInfo TrajectoryFileReaderTXT::GetFrameInfoWithStartEndPos(std::ifstream& is, TrajectoryFileFrameInfo frameInfo)
{
	std::vector<int> posFrameID;
	posFrameID.push_back(m_positions.frame);
	TrajectoryFileFrameInfo info = frameInfo;


	long pos = FileReaderHelper::SeekLineSave(is, frameInfo.pos, m_fileSize);
	long lastpos = pos;
	std::string line;
	while (pos > 0)
	{
		pos = FileReaderHelper::SeekLineSave(is, pos, m_fileSize);
		std::getline(is, line);
		if (line.size() > 0)
		{
			bool startFound = false;
			if (line.at(0) != '#')
			{
				std::vector<std::string> frameId = FileReaderHelper::GetValuesInLine(line, posFrameID);
				if (frameId.size() == 1)
				{
					int frame = atoi(frameId.at(0).c_str());
					if (frame != info.frame)
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
					if (frameId.size() == 1)
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

std::vector<Person> TrajectoryFileReaderTXT::ConvertFrameInfoToPersons(std::ifstream& is, TrajectoryFileFrameInfo frameInfo)
{
	std::vector<int> posFrameID;
	posFrameID.push_back(m_positions.id);
	posFrameID.push_back(m_positions.x);
	posFrameID.push_back(m_positions.y);
	posFrameID.push_back(m_positions.z);


	std::vector<Person> persons;
	if (frameInfo.frame != -1)
	{
		long pos = FileReaderHelper::SeekPosSave(is, frameInfo.startPos, m_fileSize);
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

std::vector<std::vector<Person>> TrajectoryFileReaderTXT::Search(int frame, int count)
{
	TrajectoryFileDataPositions positions;
	positions.id = 0;
	positions.frame = 1;
	positions.x = 2;
	positions.y = 3;
	positions.z = 4;

	std::ifstream is;
	is.open(m_filePath, std::ios_base::binary);
	if (is.fail())
	{
		throw std::invalid_argument("File not found");
	}

	std::vector<std::vector<Person>> vec;

	bool useBinaryTree = true;
	if (useBinaryTree)
	{
		BinaryTreeInformation binaryTreeInformation;
		binaryTreeInformation.startFrame = INT_MIN;
		binaryTreeInformation.startPos = m_boundaries.startPos;
		binaryTreeInformation.stopFrame = INT_MAX;
		binaryTreeInformation.stopPos = m_boundaries.stopPos;

		TrajectoryFileFrameInfo info;
		info.endPos = -1;
		info.startPos = -1;
		info.frame = -1;
		info.pos = -1;
		for (int i = 0; i < count; i++)
		{
			if (info.frame == -1)
			{
				info = SearchBinaryTree(is, binaryTreeInformation,frame + i);
			}
			else
			{
				info = SearchHelper(is, frame + i);
			}

			vec.push_back(ConvertFrameInfoToPersons(is, info));
		}
	}
	else
	{
		for (int i = 0; i < count; i++)
		{
			vec.push_back(ConvertFrameInfoToPersons(is, SearchHelper(is, frame + i)));
		}
	}

	is.close();
	return vec;
}

TrajectoryFileFrameInfo TrajectoryFileReaderTXT::SearchBinaryTree(std::ifstream& is, BinaryTreeInformation binaryTreeInformation, int searchedFrame)
{
	GlobalSettings* settings = GlobalSettings::GetInstance();

	int dif2 = binaryTreeInformation.stopPos - binaryTreeInformation.startPos;
	int pos = binaryTreeInformation.startPos + 0.5 * dif2;

	TrajectoryFileFrameInfo info1 = GetFrameInfoWithoutStartEndPos(is, pos);
	m_lastPos = info1.pos;

	int dif = searchedFrame - info1.frame;

	if (dif >= 0 && (dif <= settings->GetTxtReaderForwardThreshhold() || dif2 <= settings->GetTxtReaderBinaryTreeMinimumGap()))
	{
		TrajectoryFileFrameInfo info2 = SearchForward(is, searchedFrame, info1);
		if (info2.endPos >= 0)
		{
			m_lastPos = info2.endPos;
		}
		return info2;
	}
	if (dif < 0 && (dif >= -settings->GetTxtReaderBackwardThreshhold() || dif2 <= settings->GetTxtReaderBinaryTreeMinimumGap()))
	{
		TrajectoryFileFrameInfo info2 = SearchBackward(is, searchedFrame, info1);
		if (info2.endPos >= 0)
		{
			m_lastPos = info2.endPos;
		}
		return info2;
	}

	BinaryTreeInformation newTree;
	if (dif >= 0) //forward
	{
		newTree.startFrame = info1.frame;
		newTree.startPos = info1.pos;
		newTree.stopFrame = binaryTreeInformation.stopFrame;
		newTree.stopPos = binaryTreeInformation.stopPos;
	}
	else //backward
	{
		newTree.startFrame = binaryTreeInformation.startFrame;
		newTree.startPos = binaryTreeInformation.startPos;
		newTree.stopFrame = info1.frame;
		newTree.stopPos = info1.pos;
	}



	return SearchBinaryTree(is, newTree, searchedFrame);
}

TrajectoryFileFrameInfo TrajectoryFileReaderTXT::SearchHelper(std::ifstream& is, int frame)
{
	GlobalSettings* settings = GlobalSettings::GetInstance();
	int pos = FMath::Clamp(m_lastPos, m_boundaries.startPos, m_boundaries.stopPos);
	TrajectoryFileFrameInfo info1 = GetFrameInfoWithoutStartEndPos(is, pos);
	TrajectoryFileFrameInfo info2;
	if (info1.frame <= frame)
	{
		info2 = SearchForward(is, frame, info1);
	}
	else
	{
		info2 = SearchBackward(is, frame, info1);
	}

	if (info2.endPos >= 0)
	{
		m_lastPos = info2.endPos;
	}
	return info2;
}

TrajectoryFileFrameInfo TrajectoryFileReaderTXT::SearchForward(std::ifstream& is, int frame, TrajectoryFileFrameInfo startInfo)
{
	std::vector<int> posFrameID;
	posFrameID.push_back(m_positions.frame);

	int currentFrame = startInfo.frame;
	long pos = FileReaderHelper::SeekPosSave(is, startInfo.pos,m_fileSize);
	std::string line;
	while (currentFrame <= frame)
	{
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
			return GetFrameInfoWithStartEndPos(is, info);
		}
		pos = is.tellg();
		if (endReached || pos >= m_boundaries.stopPos)
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

TrajectoryFileFrameInfo TrajectoryFileReaderTXT::SearchBackward(std::ifstream& is, int frame, TrajectoryFileFrameInfo startInfo)
{
	std::vector<int> posFrameID;
	posFrameID.push_back(m_positions.frame);

	int currentFrame = startInfo.frame;
	long pos = FileReaderHelper::SeekPosSave(is, startInfo.pos,m_fileSize);
	std::string line;
	while (currentFrame >= frame)
	{
		pos = FileReaderHelper::SeekLineSave(is, pos,m_fileSize);
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
			return GetFrameInfoWithStartEndPos(is, info);

		}
		pos = pos - 1;
		if (endReached || pos <= m_boundaries.startPos)
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

void TrajectoryFileReaderTXT::SetFrameBoundaries()
{
	std::ifstream is;
	is.open(m_filePath, std::ios_base::binary);
	if (is.fail())
	{
		throw std::invalid_argument("File not found");
	}

	TrajectoryFileFrameBoundaries boundaries = TrajectoryFileFrameBoundaries();

	FileReaderHelper::SeekLineSave(is, 0, m_fileSize);

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

	long pos = m_fileSize - 1;
	while (pos > 0)
	{
		pos = FileReaderHelper::SeekLineSave(is, pos, m_fileSize);
		std::getline(is, line);
		if (line.size() > 0 && line.at(0) >= '0' && line.at(0) <= '9')
		{
			endFound = true;
			boundaries.stopPos = pos;
			break;
		}


		pos = pos - 1;
	}
	is.close();

	if (beginingFound && endFound)
	{
		m_boundaries = boundaries;
	}
	else
	{
		throw std::exception("file is not valid");
	}
}

void TrajectoryFileReaderTXT::SetTrajectoryFileDataPositions()
{
	m_positions.id = 0;
	m_positions.frame = 1;
	m_positions.x = 2;
	m_positions.y = 3;
	m_positions.z = 4;
}


