// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Triggerable.h"
#include "WeaponPickup.generated.h"

/**
 * 
 */
UCLASS()
class THEESCAPER_API AWeaponPickup : public ATriggerable
{
	GENERATED_BODY()

public:

	AWeaponPickup();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AWeapon> weaponClass;


	virtual void BeginPlay() override;

	//HOMEWORK
	//spawn a random weapon pickup when enemy dies
	//when we pick up a  weapon of something we already have, give the weapon more ammo instead.
	//create a health regenerate pickup.

private:

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	UStaticMeshComponent* meshComp;

	virtual void OnTriggered(AActor* actor) override;
	virtual void OnActorLeftTrigger(AActor* actor) override;

#if WITH_EDITOR

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	
};
