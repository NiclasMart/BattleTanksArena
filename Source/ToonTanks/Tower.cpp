// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::BeginPlay()
{
	ABasicPawn::BeginPlay();

	bUpdateTick = PrimaryActorTick.bCanEverTick;

	Target = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (!Target) UE_LOG(LogTemp, Error, TEXT("Can't find Player Pawn (%s)"), *GetName());
}

void ATower::Tick(float DeltaTime)
{
	ABasicPawn::Tick(DeltaTime);

	if (!Target) return;
	if (TargetInVisionRange() && Target->IsAlive())
	{
		TurnTurretToPoint(Target->GetActorLocation());
		FireProjectile();
	}
}

void ATower::FireProjectile()
{
	if (GetWorld()->GetTimeSeconds() >= LastTimeFired + FireCooldown)
	{
		FireProjectileAtLocation(Target->GetActorLocation());
		LastTimeFired = GetWorld()->GetTimeSeconds();
	}
}

void ATower::HandleDestruction()
{
	ABasicPawn::HandleDestruction();
	Destroy(this);
}

bool ATower::TargetInVisionRange()
{
	if (!Target) return false;
	float DistanceToTarget = FVector::Dist(GetActorLocation(), Target->GetTargetLocation());
	return DistanceToTarget <= VisionRange;
}


