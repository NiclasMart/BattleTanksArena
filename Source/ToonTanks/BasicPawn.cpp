// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicPawn.h"

#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "HealthComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Projectile.h"
#include "ProjectilePoolComponent.h"

// Sets default values
ABasicPawn::ABasicPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));	//attaches Capsule Component to object
	RootComponent = CapsuleComp; //override RootComponent with newly created Component (both have SceneComponent as parent)

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body Mesh"));
	BodyMesh->SetupAttachment(CapsuleComp); //Attaches Component as child hierarchical to the defined parent component (BodyMesh is child of CapsuleComp)

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BodyMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	ProjectilePoolComp = CreateDefaultSubobject<UProjectilePoolComponent>(TEXT("Projectile Pool"));
}


void ABasicPawn::BeginPlay()
{
	Super::BeginPlay();
	ProjectilePoolComp->SetProjectileClass(ProjectileClass);
}

void ABasicPawn::HandleDestruction()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, DestroyParticles, GetActorLocation(), GetActorRotation());
	UGameplayStatics::PlaySoundAtLocation(this, DestructionSound, GetActorLocation(), 0.6f, 0.3f);
	GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShake);
}

void ABasicPawn::TurnTurretToPoint(FVector Point)
{
	FVector NewLookDirection = Point - TurretMesh->GetComponentLocation();
	FRotator NewRotation = FRotator(0.f, NewLookDirection.Rotation().Yaw, 0.f);
	TurretMesh->SetWorldRotation(NewRotation);
}

void ABasicPawn::TurnTurretByAngle(FRotator Angle)
{
	TurretMesh->AddLocalRotation(Angle);
}

void ABasicPawn::FireProjectileAtLocation(FVector Location)
{
	auto Projectile = ProjectilePoolComp->GetProjectile(
		GetWorld(),
		ProjectileSpawnPoint->GetComponentLocation(),
		ProjectileSpawnPoint->GetComponentRotation()
	);

	UGameplayStatics::PlaySoundAtLocation(this, FireProjectileSound, GetActorLocation(), 0.4f, 0.3f);

	if (Projectile) Projectile->SetOwner(this);
}



