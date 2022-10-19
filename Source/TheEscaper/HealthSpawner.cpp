// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthSpawner.h"
#include "HealthPickup.h"

// Sets default values
AHealthSpawner::AHealthSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHealthSpawner::BeginPlay()
{
	Super::BeginPlay();
	healthPickup = GetWorld()->SpawnActor<AHealthPickup>(healthPickupClass, GetActorLocation(), GetActorRotation());
	healthPickup->onPickup.AddDynamic(this, &AHealthSpawner::StartTimer);
	
}

// Called every frame
void AHealthSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHealthSpawner::SpawnPickup()
{
	healthPickup->UnHidePickup();
}

void AHealthSpawner::StartTimer()
{
	GetWorldTimerManager().SetTimer(coolDownTimer, this, &AHealthSpawner::SpawnPickup, healthSpawnCooldown, false);
}

