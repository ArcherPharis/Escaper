// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameUI.generated.h"

/**
 * 
 */
UCLASS()
class THEESCAPER_API UInGameUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void UpdateHealth(float health, float delta, float maxHealth);

	UFUNCTION()
	void NewWeaponGiven(class AWeapon* weapon);

	UFUNCTION()
	void WeaponSwitched(class AWeapon* weapon);

	void SwitchToGameOverMenu();
	void SwitchToPauseMenu();

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UValueGauge* healthBar;

	UPROPERTY(meta = (BindWidget))
	class UImage* crossHair;

	UPROPERTY(meta = (BindWidget))
	class UListView* weaponList;

	UPROPERTY(meta = (BindWidget))
	class UGameMenuCanvas* inGameCanvas;

	UPROPERTY(meta = (BindWidget))
	class UGameMenuCanvas* pauseCanvas;

	UPROPERTY(meta = (BindWidget))
	class UGameMenuCanvas* gameOverCanvas;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* UISwitcher;

	UPROPERTY(meta = (bindWidget))
	class UButton* continueButton;

	UPROPERTY(meta = (bindWidget))
	class UButton* restartButton;

	UPROPERTY(meta = (bindWidget))
	class UButton* quitButton;

	UFUNCTION()
	void Resume();
	UFUNCTION()
	void Restart();
	UFUNCTION()
	void Quit();


	
	
};
