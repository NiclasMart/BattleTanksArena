// Fill out your copyright notice in the Description page of Project Settings.


#include "IDisableActor.h"

#include "GameFramework/Actor.h"

IDisableActor::IDisableActor()
{
}

IDisableActor::~IDisableActor()
{
}

void IDisableActor::DisableActor(AActor* Actor, bool bActiveState)
{
	Actor->SetActorHiddenInGame(!bActiveState);
	Actor->SetActorEnableCollision(bActiveState);

	UE_LOG(LogTemp, Warning, TEXT("%s"), *Actor->GetName());

	if (bActiveState) Actor->PrimaryActorTick.bCanEverTick = bUpdateTick;
	else Actor->PrimaryActorTick.bCanEverTick = false;
}
