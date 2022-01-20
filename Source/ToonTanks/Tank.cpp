// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"


ATank::ATank()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Springarm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 800.f;
	/*SpringArmComponent->AddWorldRotation(FRotator(0, -45.f, 0));*/

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComponent);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
	PlayerInputComponent->BindAxis(TEXT("RotateTurret"), this, &ATank::TurnTurretToMousePosition);
	PlayerInputComponent->BindAxis(TEXT("ChangeCameraDistance"), this, &ATank::ChangeCameraDistance);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::FireProjectile);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(GetController());
	if (!PlayerController) UE_LOG(LogTemp, Error, TEXT("No valid PlayerController was found on %s!"), *GetName());
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);

	bIsAlive = false;
}

void ATank::TurnTurretToMousePosition(float Value)
{
	if (!PlayerController) return;
	FHitResult Hit;
	if (PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, Hit))
	{
		TurnTurretToPoint(Hit.ImpactPoint);
		FireLocation = Hit.ImpactPoint;
	}
}

void ATank::Move(float Value)
{
	FVector ForwardMovement = FVector(Value, 0, 0);
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	FVector LocalOffset = ForwardMovement * DeltaTime * MovementSpeed;
	AddActorLocalOffset(LocalOffset, true);

	MovingDirection = Value != 0 ? Value : 1;
}

void ATank::Turn(float Value)
{
	FRotator TurnRotation = FRotator(0, Value, 0);
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	FRotator LocalRotation = TurnRotation * DeltaTime * TurningSpeed * MovingDirection;
	AddActorLocalRotation(LocalRotation, true);
}

void ATank::ChangeCameraDistance(float Value)
{
	if (Value == 0) return;
	if (!SpringArmComponent) return;

	float CurrentArmLength = SpringArmComponent->TargetArmLength;
	CurrentArmLength -= Value * UGameplayStatics::GetWorldDeltaSeconds(this)  * CameraMovementSpeed;
	SpringArmComponent->TargetArmLength = FMath::Clamp(CurrentArmLength, CameraMinDistance, CameraMaxDistance);
}

void ATank::FireProjectile()
{
	if (LastFireTime + FireCooldown <= GetWorld()->GetRealTimeSeconds())
	{
		FireProjectileAtLocation(FireLocation);
		LastFireTime = GetWorld()->GetRealTimeSeconds();
	}
	
}

