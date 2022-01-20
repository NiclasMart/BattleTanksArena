// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void ActorDied(AActor* DeadActor);
	void HandleGameEnd(bool bGameOver);

	int32 GetTowerCountForCurrentRound() const { return ActiveTowerCount; }

protected:
	virtual void InitGame(const FString & MapName, const FString & Options, FString & ErrorMessage) override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintImplementableEvent)
		void StartGame();
	UFUNCTION(BlueprintImplementableEvent)
		void EndGame(bool bGameOver);

private:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		float GameStartDelayTime = 3.f;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (AllowPrivateAccess = "true"))
		int32 TotalRoundCount = 5;
	UPROPERTY(EditAnywhere)
		int32 StartTowerCount = 5;
	UPROPERTY(EditAnywhere)
		int32 TowerIncreasementEachRound = 2;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		int32 CurrentRound = 0;
	

	class ATank* Tank = nullptr;
	class ATankPlayerController* TankPlayerController = nullptr;
	int32 ActiveTowerCount = 0;
	


	void HandleGameStart();
	void SetTimerForEnablingPlayer();
	void SetupNewRound();

	void SaveRoundData();
	void LoadRoundData();

};
