// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Gun.generated.h"




/**
 * 
 */
UCLASS()
class THEESCAPER_API AGun : public AWeapon
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void CanFire() override;

	virtual void ReloadWeapon() override;

	virtual void Attack() override;

	




private:

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName MuzzleSocketName;


	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float shootRange = 10000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float damage = 10.f;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	int ammo = 10;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	int maxAmmo = 10;

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* reloadMontage;

	virtual void AttackPointAnimNotify() override;
	virtual void ReloadAnimNotify() override;
	void SetInitialAmmo();

	class APlayerCharacter* player;
	
};
