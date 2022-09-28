// Fill out your copyright notice in the Description page of Project Settings.


#include "EEnemy.h"
#include "Components/WidgetComponent.h"
#include "ValueGauge.h"

AEEnemy::AEEnemy()
{
	healthBarWidgetComp = CreateDefaultSubobject<UWidgetComponent>("HealthBarComp");
	healthBarWidgetComp->SetupAttachment(GetRootComponent());
}

void AEEnemy::BeginPlay()
{
	Super::BeginPlay();
	 valueGauge = Cast<UValueGauge>( healthBarWidgetComp->GetUserWidgetObject());
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
}
