// Fill out your copyright notice in the Description page of Project Settings.


#include "CacheAsyncLoader.h"

#include "Cache.h"

CacheAsyncLoader::CacheAsyncLoader()
{
}

CacheAsyncLoader::CacheAsyncLoader(std::shared_ptr<Cache> cache)
{
	m_cache = cache;
}

CacheAsyncLoader::~CacheAsyncLoader()
{
}

void CacheAsyncLoader::DoWork()
{
	while (true)
	{
		m_cache.get()->CheckToLoad();
	}
}
