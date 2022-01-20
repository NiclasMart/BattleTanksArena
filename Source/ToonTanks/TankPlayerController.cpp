// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

void ATankPlayerController::SetupPlayerEnabledState(bool bPlayerEnabled)
{
	UE_LOG(LogTemp, Warning, TEXT("Player Controller Called with %d"), bPlayerEnabled);
	if (bPlayerEnabled) GetPawn()->EnableInput(this);
	else GetPawn()->DisableInput(this);

	bShowMouseCursor = bPlayerEnabled;
}

