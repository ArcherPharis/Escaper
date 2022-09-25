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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UAnimMontage* GetAttackMontage() const;

	UFUNCTION(BlueprintPure)
	UAnimSequence* GetIdleAnim() const;

	UFUNCTION(BlueprintPure)
	UAnimSequence* GetWalkAnim() const;



private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	class USceneComponent* RootComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	class UStaticMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimSequence* idleAnim;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimSequence* walkAnim;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* attackMontage;


};
