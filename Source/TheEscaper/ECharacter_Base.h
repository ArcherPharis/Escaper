// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ECharacter_Base.generated.h"

#define ECC_Character ECC_GameTraceChannel1

class AWeapon;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponGiven, AWeapon*, weapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponSwitched, AWeapon*, weapon);




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

	FOnWeaponGiven OnWeaponGiven;
	FOnWeaponSwitched OnWeaponSwitched;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void GiveWeapon(TSubclassOf<AWeapon> weaponClass);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	FORCEINLINE	AWeapon* GetCurrentWeapon() const { return currentWeapon; }
	FORCEINLINE class UHealthComponent* GetHealthComp() const { return healthComp; }

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



protected:
	void Attack();

	void PrevWeapon();
	void NextWeapon();

	UFUNCTION()
	void Reload();

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

	

	UPROPERTY(VisibleDefaultsOnly, Category = "Health")
	class UHealthComponent* healthComp;

	UFUNCTION()
	void HealthChanged(float val, float delta, float max);
	
	UFUNCTION()
	void StartDeathSequence();

	virtual void OnHealthChange(float val, float delta, float max);
	virtual void OnDeathStart();

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* DeathMontage;

	void Dead();
	FTimerHandle DeathTimerHandle;
	bool bIsDead = false;

	void DisableGameplayRelevancy();

};
