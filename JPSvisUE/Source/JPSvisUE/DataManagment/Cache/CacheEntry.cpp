// Fill out your copyright notice in the Description page of Project Settings.


#include "CacheEntry.h"

CacheEntry::CacheEntry()
{
}

CacheEntry::CacheEntry(std::vector<Person> persons)
{
	m_persons = persons;
}

std::vector<Person>& CacheEntry::GetPersons()
{
	return m_persons;
}

CacheEntry::~CacheEntry()
{
}
