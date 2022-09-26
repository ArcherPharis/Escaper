// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnAcquired(class USkeletalMeshComponent* ownerMeshComponent);

	void Attack();

	UFUNCTION(BlueprintPure, Category = "Animation")
	void GetAnims(UAnimSequence*& Idle, UAnimSequence*& Walk, UAnimMontage*& Attack) const;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void AttackPointAnimNotify();

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	class USceneComponent* RootComp;



	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimSequence* IdleAnim;
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimSequence* WalkAnim;
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponSocket;

	USkeletalMeshComponent* OwnerSkeletalMesh;

	void CanFire();
	UPROPERTY(EditAnywhere, Category = "Weapon")
	float fireRate = 1.f;
	bool canFire = true;
};
