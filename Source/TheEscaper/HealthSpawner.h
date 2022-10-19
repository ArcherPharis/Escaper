// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealthSpawner.generated.h"

UCLASS()
class THEESCAPER_API AHealthSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealthSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere, Category = "Health Pickup")
	float healthSpawnCooldown = 2.f;

	UPROPERTY(EditDefaultsOnly, Category = "Health Pickup")
	TSubclassOf<class AHealthPickup> healthPickupClass;

	AHealthPickup* healthPickup;

	void SpawnPickup();
	
	UFUNCTION()
	void StartTimer();



	FTimerHandle coolDownTimer;


};
