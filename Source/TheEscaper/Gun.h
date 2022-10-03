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

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon", meta = (DisplayName="OnBulletHit"))
	void BP_OnBulletHit(const FHitResult& hitResult);

private:

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName MuzzleSocketName;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	int ammoInClip = 7;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	int clipCapacity = 7;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	int ammoInventory = 30;


	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float shootRange = 10000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float damage = 10.f;

	virtual void AttackPointAnimNotify() override;

	virtual void Reload() override;
	bool IsReloading() const;
	FTimerHandle ReloadTimerHandle;

	void ReloadTimePoint();
	virtual void PutInInventory() override;
	virtual bool GetAmmoStatus(int& clipAmmo, int& inventoryAmmo) const override;
};
