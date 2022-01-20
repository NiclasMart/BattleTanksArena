// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectilePoolComponent.h"
#include "Projectile.h"

// Sets default values for this component's properties
UProjectilePoolComponent::UProjectilePoolComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UProjectilePoolComponent::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void UProjectilePoolComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UProjectilePoolComponent::SetProjectileClass(TSubclassOf<AProjectile> ProjectileClass)
{
	ProjectileBlueprint = ProjectileClass;
}

AProjectile* UProjectilePoolComponent::GetProjectile(UWorld* World, FVector Location, FRotator Rotation)
{
	if (Pool.Num() == 0) return GenerateNewProjectile(World, Location, Rotation);
	else
	{
		AProjectile* ProjectileFromPool = Pool.Pop();
		ProjectileFromPool->PrepareLaunch(Location, Rotation);
		return ProjectileFromPool;
	}
}

void UProjectilePoolComponent::RepoolObject(class AProjectile* Projectile)
{
	if (Pool.Num() >= MaxPoolSize) Projectile->Destroy();

	Pool.Push(Projectile);
}

AProjectile* UProjectilePoolComponent::GenerateNewProjectile(UWorld* World, FVector Location, FRotator Rotation)
{
	if (!ProjectileBlueprint) UE_LOG(LogTemp, Error, TEXT("There is no projectile Class be assigned to the Projectile Pool."));
	return World->SpawnActor<AProjectile>(ProjectileBlueprint, Location, Rotation);
}

