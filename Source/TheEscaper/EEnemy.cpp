// Fill out your copyright notice in the Description page of Project Settings.


#include "EEnemy.h"
#include "Components/WidgetComponent.h"
#include "ValueGauge.h"
#include "PatrollingComponent.h"
#include "WeaponPickup.h"

AEEnemy::AEEnemy()
{
	healthBarWidgetComp = CreateDefaultSubobject<UWidgetComponent>("HealthBarComp");
	healthBarWidgetComp->SetupAttachment(GetRootComponent());
	PatrollingPoint = CreateDefaultSubobject<UPatrollingComponent>(TEXT("PatrollingComp"));
}

void AEEnemy::BeginPlay()
{
	Super::BeginPlay();
	 valueGauge = Cast<UValueGauge>( healthBarWidgetComp->GetUserWidgetObject());
	 chanceToDrop = FMath::Clamp(chanceToDrop, 0, 100);
}

void AEEnemy::OnHealthChange(float val, float delta, float max)
{
	if (valueGauge)
	{
		valueGauge->SetValue(val, delta, max);
	}
}

void AEEnemy::OnDeathStart()
{
	int randomNum = FMath::RandRange(1, 100);

	if (randomNum <= chanceToDrop)
	{
		if (weaponPickUp)
		{
			AWeaponPickup* weaponPU = GetWorld()->SpawnActor<AWeaponPickup>(weaponPickUp);
			weaponPU->SetActorLocation(GetActorLocation());
			weaponPU->SetRandomWeapon();
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("no item for you"));
	}

	
}
