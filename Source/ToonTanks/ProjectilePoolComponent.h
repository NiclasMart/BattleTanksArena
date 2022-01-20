// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectilePoolComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UProjectilePoolComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UProjectilePoolComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetProjectileClass(TSubclassOf<class AProjectile> ProjectileClass);
	class AProjectile* GetProjectile(UWorld* World, FVector Location, FRotator Rotation);
	void RepoolObject(class AProjectile* Projectile);

private:
	UPROPERTY()
		TSubclassOf<class AProjectile>ProjectileBlueprint;

	int MaxPoolSize = 50;
	TArray<class AProjectile*> Pool;

	class AProjectile* GenerateNewProjectile(UWorld* World, FVector Location, FRotator Rotation);
};
