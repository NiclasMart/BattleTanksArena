// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class TOONTANKS_API IDisableActor
{
public:
	IDisableActor();
	~IDisableActor();

	void DisableActor(AActor* Actor, bool bActiveState);
	bool bUpdateTick = false;
};
