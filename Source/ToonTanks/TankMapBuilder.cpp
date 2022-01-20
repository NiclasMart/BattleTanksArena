// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMapBuilder.h"

#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "Wall.h"
#include "Tower.h"
#include "ToonTanksGameMode.h"


// Sets default values
ATankMapBuilder::ATankMapBuilder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATankMapBuilder::BeginPlay()
{
	Super::BeginPlay();

	//Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this))->OnFinishedLoading.AddDynamic(this, &ATankMapBuilder::SetActiveTowers);
	DisableWallSegments();
	SetActiveTowers();
}

// Called every frame
void ATankMapBuilder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATankMapBuilder::SetActiveTowers()
{
	TArray<AActor*> TowerActors;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), TowerActors);

	AToonTanksGameMode* GameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));
	int32 TowerActiveCount = GameMode ? GameMode->GetTowerCountForCurrentRound() : 0;

	//UE_LOG(LogTemp, Warning, TEXT("TowerActive: %d"), TowerActiveCount);
	int32 TowerDisableCount = FMath::Max(TowerActors.Num() - TowerActiveCount, 0);

	for (int32 i = 0; i < TowerDisableCount; i++)
	{
		if (TowerActors.Num() == 0) break;
		int32 index = FMath::RandRange(0, TowerActors.Num() - 1);
		ATower* Tower = Cast<ATower>(TowerActors[index]);
		if (!Tower) continue;

		Tower->DisableActor(TowerActors[index], false);
		TowerActors.RemoveAt(index);
	}
}

void ATankMapBuilder::DisableWallSegments()
{
	int WallDisableCount = DisabledWallQuantity * WallList.Num();
	for (int32 i = 0; i < WallDisableCount; i++)
	{
		if (WallList.Num() == 0) break;
		int32 index = FMath::RandRange(0, WallList.Num() - 1);
		WallList[index]->DisableActor(WallList[index], false);
		WallList.RemoveAt(index);
	}
}



