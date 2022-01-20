// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "BasicPawn.h"
#include "Camera/CameraShakeBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectilePoolComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundBase.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	RootComponent = ProjectileMesh;

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	MovementComp->InitialSpeed = 1500.f;
	MovementComp->MaxSpeed = 1500.f;

	SmokeTrailComponent = CreateDefaultSubobject <UParticleSystemComponent>(TEXT("Smoke Trail"));
	SmokeTrailComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation(), GetActorRotation());
	UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
	GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(FireCameraShake);
	
	if (OtherActor)
	{
		auto MyOwner = GetOwner();
		UE_LOG(LogTemp, Warning, TEXT("Projectile hit"));
		if (MyOwner && OtherActor != this && OtherActor != MyOwner)
		{
			UGameplayStatics::ApplyDamage(
				OtherActor,
				Damage,
				GetOwner()->GetInstigatorController(),
				this,
				UDamageType::StaticClass()
			);
		}
	}
	Disable();	
}

void AProjectile::PrepareLaunch(FVector Location, FRotator Rotation)
{
	SetTransform(Location, Rotation);
	SetActiveState(true);
	
	MovementComp->Velocity = Rotation.Vector() * MovementComp->InitialSpeed;
	MovementComp->SetUpdatedComponent(GetRootComponent());
}

void AProjectile::Disable()
{
	SetActiveState(false);

	auto MyOwner = Cast<ABasicPawn>(GetOwner());
	if (MyOwner && MyOwner->GetProjectilePool()) MyOwner->GetProjectilePool()->RepoolObject(this);
}

void AProjectile::SetTransform(FVector Location, FRotator Rotation)
{
	SetActorLocation(Location);
	SetActorRotation(Rotation);
}

void AProjectile::SetActiveState(bool bActive)
{
	SetActorHiddenInGame(!bActive);
	SetActorEnableCollision(bActive);

	if (bActive) MovementComp->Activate(true);
	else MovementComp->Deactivate();
}

