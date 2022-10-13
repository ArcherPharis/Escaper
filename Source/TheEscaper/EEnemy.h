// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ECharacter_Base.h"
#include "EEnemy.generated.h"

/**
 * 
 */
UCLASS()
class THEESCAPER_API AEEnemy : public AECharacter_Base
{
	GENERATED_BODY()

public:
	AEEnemy();
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "UI")
	class UWidgetComponent* healthBarWidgetComp;
	class UValueGauge* valueGauge;

	virtual void OnHealthChange(float val, float delta, float max) override;
	virtual void OnDeathStart() override;

	UPROPERTY(EditAnywhere, Category = "Patrolling")
	class UPatrollingComponent* PatrollingPoint;

	UPROPERTY(EditAnywhere, Category = "Loot Drop")
	int chanceToDrop = 30;

	UPROPERTY(EditAnywhere, Category = "Loot Drop")
	TSubclassOf<class AWeaponPickup> weaponPickUp;
	
};
