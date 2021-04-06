// Fill out your copyright notice in the Description page of Project Settings.


#include "CacheLine.h"

CacheLine::CacheLine()
{
	m_isValid = false;
}

CacheLine::CacheLine(int tag, std::vector<CacheEntry>& entries, int lruID)
{
	m_isValid = true;
	m_entries = entries;
	m_tag = tag;
	m_lruID = lruID;
}

CacheLine::~CacheLine()
{
}

int CacheLine::GetTag()
{
	return m_tag;
}

bool CacheLine::GetIsValid()
{
	return m_isValid;
}

CacheEntry& CacheLine::GetEntry(int wordOffset)
{
	return m_entries.at(wordOffset);
}

inline unsigned int CacheLine::GetLruID()
{
	return m_lruID;
}

void CacheLine::SetLruID(unsigned int lruID)
{
	m_lruID = lruID;
}
