// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <vector>

class CacheEntry;
/**
 * 
 */
class JPSVISUE_API CacheLine
{
public:
	CacheLine();
	CacheLine(int tag, std::vector<CacheEntry> &entries, int lruID);
	~CacheLine();
	int GetTag();
	bool GetIsValid();
	CacheEntry& GetEntry(int wordOffset);

	unsigned int GetLruID();
	void SetLruID(unsigned int lruID);
private:
	unsigned int m_lruID;
	int m_tag;
	bool m_isValid;
	std::vector<CacheEntry> m_entries;
};
