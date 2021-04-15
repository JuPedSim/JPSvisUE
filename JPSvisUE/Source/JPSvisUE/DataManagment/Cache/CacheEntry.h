// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <vector>
#include "CoreMinimal.h"

/**
 *
 */
struct Person {
	int id;
	float x;
	float y;
	float z;
};
class JPSVISUE_API CacheEntry
{
public:
	CacheEntry();
	CacheEntry(std::vector<Person> persons);
	std::vector<Person>& GetPersons();
	~CacheEntry();
private:
	std::vector<Person> m_persons;
};
