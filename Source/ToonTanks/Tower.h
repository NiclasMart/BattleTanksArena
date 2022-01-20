// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicPawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasicPawn
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;

	void FireProjectile();

	void HandleDestruction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		float VisionRange = 1000.f;

	class ATank* Target = nullptr;

	float LastTimeFired = 10.f;

	bool TargetInVisionRange();
};
