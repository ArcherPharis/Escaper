// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ECharacter_Base.generated.h"

#define ECC_Character ECC_GameTraceChannel1

class AWeapon;

UCLASS()
class THEESCAPER_API AECharacter_Base : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AECharacter_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void GiveWeapon(TSubclassOf<AWeapon> weaponClass);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	FORCEINLINE	AWeapon* GetCurrentWeapon() const { return currentWeapon; }

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



protected:
	void Attack();

	void PrevWeapon();
	void NextWeapon();

private:

	UPROPERTY(EditDefaultsOnly, Category = "Animaiton")
	UAnimMontage* WeaponSwitchMontage;

	FTimerHandle WeaponSwitchingHandle;
	void WeaponSwitchTimePoint();

	UPROPERTY()
	TArray<AWeapon*> weapons;

	AWeapon* currentWeapon;
	int weaponIndex = -1;

	bool HasWeaponOfType(TSubclassOf<AWeapon> weaponClass) const;

	void EquipWeapon(int index);

};
