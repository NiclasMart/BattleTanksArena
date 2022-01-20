// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PrepareLaunch(FVector Location, FRotator Rotation);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* ProjectileMesh;
	UPROPERTY(VisibleAnywhere)
		class UProjectileMovementComponent* MovementComp;

	UPROPERTY(VisibleAnywhere)
		class UParticleSystemComponent* SmokeTrailComponent;
	UPROPERTY(EditAnywhere)
		class UParticleSystem* HitParticle;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCameraShakeBase> FireCameraShake;
	UPROPERTY(EditAnywhere)
		class USoundBase* HitSound;
	UPROPERTY(EditAnywhere)
		float Damage = 20.f;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void Disable();
	void SetTransform(FVector Location, FRotator Rotation);
	void SetActiveState(bool bActive);
};
