// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAmmoUpdated, int, ammoInClip, int, ammoInInventory);

UCLASS()
class THEESCAPER_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	class UStaticMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TMap<USkeletalMesh*, UAnimMontage*> ReloadAnimMap;
	UAnimMontage* ReloadMontage;

	virtual bool CanAttack() const;

	bool canFire = true;

public:	

	FOnAmmoUpdated OnAmmoUpdated;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnAcquired(class USkeletalMeshComponent* ownerMeshComponent);

	virtual void Attack();
	virtual void Reload();

	virtual void PutInInventory();
	virtual void PutInHand();

	virtual void GiveAmmoAsPickup();


	UFUNCTION(BlueprintPure, Category = "Animation")
	void GetAnims(UAnimSequence*& Idle, UAnimSequence*& Walk, UAnimMontage*& Attack) const;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void AttackPointAnimNotify();


	UFUNCTION(BlueprintCallable, Category = "Weapon")
	FORCEINLINE USkeletalMeshComponent* GetOwnerSkeletalMesh() const { return OwnerSkeletalMesh; }


	float GetWeaponDamage() const { return damage; }

	FORCEINLINE UTexture2D* GetCrossHairTexture() const { return crossHairTexture; }
	FORCEINLINE UTexture2D* GetWeaponIcon() const { return weaponIconTexture; }

	UStaticMesh* GetMesh() const { return WeaponMesh->GetStaticMesh(); }


	/*
	 @ return - false if not firearm
	*/
	virtual bool GetAmmoStatus(int& clipAmmo, int& inventoryAmmo) const;

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	class USceneComponent* RootComp;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float damage = 10.f;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TMap<USkeletalMesh*, UAnimSequence*> IdleAnimMap;
	UAnimSequence* IdleAnim;
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TMap<USkeletalMesh*, UAnimSequence*> WalkAnimMap;
	UAnimSequence* WalkAnim;
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TMap<USkeletalMesh*, UAnimMontage*> AttackAnimMap;
	UAnimMontage* AttackMontage;


	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponSocket;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	UTexture2D* crossHairTexture;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	UTexture2D* weaponIconTexture;

	USkeletalMeshComponent* OwnerSkeletalMesh;



	UPROPERTY(EditAnywhere, Category = "Weapon")
	float fireRate = 1.f;

	FTimerHandle FiringTimer;
	
};
