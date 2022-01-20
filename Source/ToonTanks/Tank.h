// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicPawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasicPawn
{
	GENERATED_BODY()
	
public:
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void HandleDestruction();
	void TurnTurretToMousePosition(float Value);
	void FireProjectile();

	APlayerController* GetPlayerController() const { return PlayerController; };
	bool IsAlive() const { return bIsAlive; };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
		class USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* CameraComp;
	UPROPERTY(EditAnywhere, Category="Movement")
		float MovementSpeed = 1.f;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float TurningSpeed = 1.f;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float TurretTurnSpeed = 1.f;
	UPROPERTY(EditAnywhere, Category = "Camera")
		float CameraMinDistance = 300.f;
	UPROPERTY(EditAnywhere, Category = "Camera")
		float CameraMaxDistance = 2000.f;
	UPROPERTY(EditAnywhere, Category = "Camera")
		float CameraMovementSpeed = 1.f;

	float MovingDirection = 1.f;
	float LastFireTime = 0;
	bool bIsAlive = true;
	FVector FireLocation;
	APlayerController* PlayerController = nullptr;

	void Move(float Value);
	void Turn(float Value);
	void ChangeCameraDistance(float Value);
};
