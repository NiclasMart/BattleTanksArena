// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "RoundSaver.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API URoundSaver : public USaveGame
{
	GENERATED_BODY()
	
public:
	URoundSaver();

	UPROPERTY()
		int32 CurrentRound = 0;

};
