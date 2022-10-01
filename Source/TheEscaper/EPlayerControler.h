// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EPlayerControler.generated.h"

/**
 * 
 */
UCLASS()
class THEESCAPER_API AEPlayerControler : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void OnPossess(APawn* newPawn) override;
	AEPlayerControler();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void GetAmmoInfo(int value);


private:
	class APlayerCharacter* playerCharacter;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	TSubclassOf<APawn> deathPawnClass;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	TSubclassOf<class UInGameUI> inGameUIClass;

	UInGameUI* inGameUI;

	UFUNCTION()
	void PawnDead();
	
};
