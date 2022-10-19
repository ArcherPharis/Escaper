// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Triggerable.h"
#include "HealthPickup.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPickup);

UCLASS()
class THEESCAPER_API AHealthPickup : public ATriggerable
{
	GENERATED_BODY()

public:
	AHealthPickup();

	FOnPickup onPickup;

	void UnHidePickup();


private:


	virtual void OnTriggered(AActor* actor) override;
	virtual void OnActorLeftTrigger(AActor* actor) override;

	void HidePickup();

	UPROPERTY(VisibleAnywhere, Category = "Health")
	UStaticMeshComponent* meshComp;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	float healAmount = 30;
	
};
