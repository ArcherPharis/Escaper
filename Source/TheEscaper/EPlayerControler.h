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

	void Caught();

	void PauseGame();

	UFUNCTION()
	void QuitGame();




private:
	class APlayerCharacter* playerCharacter;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	float afterDeathMenuTime = 3.f;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	TSubclassOf<APawn> deathPawnClass;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	TSubclassOf<class UInGameUI> inGameUIClass;

	UInGameUI* inGameUI;
	FTimerHandle CaughtTimerHandle;
	FTimerHandle DeathTimerHandle;

	void CaughtFinished();
	void AfterPlayerDeath();

	bool bIsCaught;

	UFUNCTION()
	void PawnDead();

	UFUNCTION()
	void ResumeGame();

	UFUNCTION()
	void RestartGame();



	
	
};
