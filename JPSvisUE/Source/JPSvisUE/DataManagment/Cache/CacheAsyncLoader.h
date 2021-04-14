// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include <memory>

class Cache;
/**
 * 
 */
class JPSVISUE_API CacheAsyncLoader : public FNonAbandonableTask 
{
public:
	CacheAsyncLoader();
	CacheAsyncLoader(std::shared_ptr<Cache> cache);
	~CacheAsyncLoader();

	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(CacheAsyncLoader,STATGROUP_ThreadPoolAsyncTasks);
	}
	void DoWork();
private:
	std::shared_ptr<Cache> m_cache;
};
