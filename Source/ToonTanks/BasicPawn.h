// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "IDisableActor.h"
#include "BasicPawn.generated.h"

UCLASS()
class TOONTANKS_API ABasicPawn : public APawn, public IDisableActor
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasicPawn();

	void HandleDestruction();

	class UProjectilePoolComponent* GetProjectilePool() const { return ProjectilePoolComp; };

protected:
	virtual void BeginPlay() override;

	void TurnTurretToPoint(FVector Point);
	void TurnTurretByAngle(FRotator Angle);
	void FireProjectileAtLocation(FVector Location);

	UPROPERTY(EditAnywhere)
		float FireCooldown = 3.f;
	

private:
	UPROPERTY(VisibleAnywhere)
		class UCapsuleComponent* CapsuleComp;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* BodyMesh;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleAnywhere)
		USceneComponent* ProjectileSpawnPoint;
	UPROPERTY(VisibleAnywhere)
		class UHealthComponent* HealthComp;
	UPROPERTY(EditAnywhere)
	class UProjectilePoolComponent* ProjectilePoolComp = nullptr;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCameraShakeBase> DeathCameraShake;

	UPROPERTY(EditAnywhere)
		class  UParticleSystem* DestroyParticles;
	UPROPERTY(EditAnywhere)
		class USoundBase* FireProjectileSound;
	UPROPERTY(EditAnywhere)
		USoundBase* DestructionSound;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AProjectile> ProjectileClass;
};
