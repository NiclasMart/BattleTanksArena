// Fill out your copyright notice in the Description page of Project Settings.


#include "Wall.h"

#include "IDisableActor.h"

// Sets default values
AWall::AWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall Mesh"));
	RootComponent = WallMesh;
}

// Called when the game starts or when spawned
void AWall::BeginPlay()
{
	AActor::BeginPlay();

	bUpdateTick = PrimaryActorTick.bCanEverTick;
}

// Called every frame
void AWall::Tick(float DeltaTime)
{
	AActor::Tick(DeltaTime);

}

