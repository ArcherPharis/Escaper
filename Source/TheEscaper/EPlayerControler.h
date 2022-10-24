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

	void SetUIHidden(bool bHideUI);

	void Caught();

	void PauseGame();

	UFUNCTION()
	void QuitGame();

	void BossDefeated();
	void DelayPause();

	void PlayBossMusic();




private:
	class APlayerCharacter* playerCharacter;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	float afterDeathMenuTime = 3.f;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	TSubclassOf<APawn> deathPawnClass;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	TSubclassOf<class UInGameUI> inGameUIClass;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	class UAudioComponent* audioComponent;
	UPROPERTY(EditDefaultsOnly, Category = "Music")
	USoundBase* backgroundMusic;
	UPROPERTY(EditDefaultsOnly, Category = "Music")
	USoundBase* bossMusic;



	UInGameUI* inGameUI;
	FTimerHandle CaughtTimerHandle;
	FTimerHandle DeathTimerHandle;
	FTimerHandle PauseTimerHandle;

	float pauseDelay = 5.f;


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
