// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "RoundSaver.h"
#include "Tank.h"
#include "TankPlayerController.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"


void AToonTanksGameMode::InitGame(const FString & MapName, const FString & Options, FString & ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	LoadRoundData();

	int32 RoundMultiplicator = CurrentRound - 1;
	ActiveTowerCount = StartTowerCount + RoundMultiplicator * TowerIncreasementEachRound;

	UE_LOG(LogTemp, Error, TEXT("%d"), ActiveTowerCount);
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	HandleGameStart();
}

void AToonTanksGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (EndPlayReason == EEndPlayReason::Quit || EndPlayReason == EEndPlayReason::EndPlayInEditor)
	{
		UE_LOG(LogTemp, Error, TEXT("Reset Rounds"));
		CurrentRound = 0;
		SaveRoundData();
	}
}

void AToonTanksGameMode::HandleGameStart()
{
	StartGame();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (!Tank) UE_LOG(LogTemp, Error, TEXT("No Player found in GameMode Class!"));

	TankPlayerController = Cast<ATankPlayerController>(Tank->GetController());
	UE_LOG(LogTemp, Warning, TEXT("Begin game"));

	if (TankPlayerController) SetTimerForEnablingPlayer();
}

void AToonTanksGameMode::SetTimerForEnablingPlayer()
{
	TankPlayerController->SetupPlayerEnabledState(false);

	FTimerHandle GameStartTimer = FTimerHandle();
	FTimerDelegate StartGameDelegate = FTimerDelegate::CreateUObject(	//create Delegate to call function after specific time with parameters
		TankPlayerController,
		&ATankPlayerController::SetupPlayerEnabledState,
		true
	);
	GetWorldTimerManager().SetTimer(	//set time with delegate 
		GameStartTimer,
		StartGameDelegate,
		GameStartDelayTime,
		false
	);
}

void AToonTanksGameMode::SetupNewRound()
{
	SaveRoundData();
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void AToonTanksGameMode::SaveRoundData()
{
	CurrentRound = (CurrentRound >= TotalRoundCount) ? 1 : CurrentRound+1;

	URoundSaver* RoundSaver = Cast<URoundSaver>(UGameplayStatics::CreateSaveGameObject(URoundSaver::StaticClass()));
	RoundSaver->CurrentRound = CurrentRound;
	UGameplayStatics::SaveGameToSlot(RoundSaver, TEXT("SavedRoundSlot"), 0);
}

void AToonTanksGameMode::LoadRoundData()
{
	URoundSaver* RoundSaver = Cast<URoundSaver>(UGameplayStatics::CreateSaveGameObject(URoundSaver::StaticClass()));
	auto SaveData = UGameplayStatics::LoadGameFromSlot(TEXT("SavedRoundSlot"), 0);
	if (SaveData)
	{
		RoundSaver = Cast<URoundSaver>(SaveData);
		CurrentRound = RoundSaver->CurrentRound;
	}
}

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank) 
	{
		HandleGameEnd(true);
	}
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
		--ActiveTowerCount;

		UE_LOG(LogTemp, Error, TEXT("%d"), ActiveTowerCount);
		if (ActiveTowerCount == 0) HandleGameEnd(false);
	}
}

void AToonTanksGameMode::HandleGameEnd(bool bGameOver)
{
	if (bGameOver)
	{
		Tank->HandleDestruction();
		CurrentRound = 0;
		if (TankPlayerController) TankPlayerController->SetupPlayerEnabledState(false);
	}

	EndGame(bGameOver);

	//set timer for loading next round
	FTimerHandle RoundEndTimer = FTimerHandle();
	GetWorldTimerManager().SetTimer(RoundEndTimer, this, &AToonTanksGameMode::SetupNewRound, 3.f, false);
}

