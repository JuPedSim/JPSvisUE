// Fill out your copyright notice in the Description page of Project Settings.


#include "FileReaderHelper.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <algorithm>

FileReaderHelper::FileReaderHelper()
{
}

FileReaderHelper::~FileReaderHelper()
{
}

long FileReaderHelper::SeekLineSave(std::ifstream& is, long pos, long size)
{
	pos = FileReaderHelper::GetPositionBeforeNewLineIfNeeded(is, pos, size);

	char* c = new char[1];
	bool beginingNotFound = true;
	bool onlyNewLine = true;
	bool lineFeed = false;
	bool carriageReturn = true;
	while (beginingNotFound)
	{
		pos = FileReaderHelper::SeekPosSave(is, pos, size);
		if (pos == 0)
		{
			beginingNotFound = false;
		}
		is.read(c, 1);
		if (c[0] == '\n' || c[0] == '\r')
		{
			beginingNotFound = false;
		}
		if (beginingNotFound)
		{
			pos--;
		}
	}
	delete(c);
	pos++;
	return FileReaderHelper::SeekPosSave(is, pos, size);
}

long FileReaderHelper::SeekPosSave(std::ifstream& is, long pos, long size)
{
	if (pos < 0)
	{
		pos = 0;
	}
	if (pos >= size)
	{
		pos = size - 1;
	}
	if (is.eofbit)
	{
		is.clear();
	}
	is.seekg(std::streampos(pos));
	return pos;
}

long FileReaderHelper::GetSize(std::string path)
{
	/*struct stat sBuffer;
	const char* acFileName = path.c_str();
	stat(acFileName, &sBuffer);
	return sBuffer.st_size;*/
	std::ifstream in(path, std::ifstream::ate | std::ifstream::binary);
	return in.tellg();
}

std::vector<std::string> FileReaderHelper::GetValuesInLine(std::string line, std::vector<int> positons)
{
	std::vector<std::string> values;

	std::string val = "";
	for (int i = 0;i< line.size();i++) 
	{
		if (line.at(i)=='\t') 
		{
			values.push_back(val);
			val = "";
		}
		else
		{
			val+=line.at(i);
		}
	}
	values.push_back(val);

	std::vector<std::string> searchedValues;
	searchedValues.resize(positons.size());
	for (int i = 0;i<positons.size();i++) 
	{
		int pos = positons.at(i);
		if (pos>=values.size()) 
		{
			return std::vector<std::string>();
		}
		searchedValues.at(i) = values.at(pos);
	}
	return searchedValues;
}

long FileReaderHelper::GetPositionBeforeNewLineIfNeeded(std::ifstream& is, long pos, long size)
{
	char* c = new char[1];
	pos = FileReaderHelper::SeekPosSave(is, pos, size);
	is.read(c, 1);
	if (c[0] == '\n')
	{
		pos--;
		pos = FileReaderHelper::SeekPosSave(is, pos, size);
		is.read(c, 1);
		if (c[0] == '\r')
		{
			pos--;
		}
		return pos;
	}
	else
	{
		return pos;
	}
	if (c[0] == '\r')
	{
		pos--;
		return pos;
	}
	return pos;
}
