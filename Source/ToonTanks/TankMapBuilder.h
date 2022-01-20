// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TankMapBuilder.generated.h"

UCLASS()
class TOONTANKS_API ATankMapBuilder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATankMapBuilder();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetActiveTowers();
	void DisableWallSegments();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category="Wall Parameter")
	TArray<class AWall*> WallList;

	UPROPERTY(EditAnywhere, Category = "Wall Parameter", meta=(ClampMin="0", ClampMax="1"))
		float DisabledWallQuantity = 0;
};
