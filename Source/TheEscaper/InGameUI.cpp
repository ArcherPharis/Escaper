// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUI.h"
#include "ValueGauge.h"
#include "Components/Image.h"
#include "Components/ListView.h"
#include "Weapon.h"
#include "GameMenuCanvas.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
//#include "Blueprint/WidgetBlueprintLibrary.h"


void UInGameUI::NativeConstruct()
{
	Super::NativeConstruct();
	continueButton->OnReleased.AddDynamic(this, &UInGameUI::Resume);
	restartButton->OnReleased.AddDynamic(this, &UInGameUI::Restart);
	quitButton->OnReleased.AddDynamic(this, &UInGameUI::Quit);
	restartButtonGameOver->OnReleased.AddDynamic(this, &UInGameUI::Restart);
	quitButtonGameOver->OnReleased.AddDynamic(this, &UInGameUI::Quit);
	restartButtonWin->OnReleased.AddDynamic(this, &UInGameUI::Restart);
	quitButtonWin->OnReleased.AddDynamic(this, &UInGameUI::Quit);



}

void UInGameUI::Resume()
{

	OnGameResumed.Broadcast();
	UISwitcher->SetActiveWidgetIndex(inGameCanvas->GetCanvasIndex());
	
}

void UInGameUI::Restart()
{
	OnGameRestarted.Broadcast();
}

void UInGameUI::Quit()
{
	OnGameQuit.Broadcast();
}



void UInGameUI::UpdateHealth(float health, float delta, float maxHealth)
{

	healthBar->SetValue(health, delta, maxHealth);
}

void UInGameUI::NewWeaponGiven(AWeapon* weapon)
{
	weaponList->AddItem(weapon);
}

void UInGameUI::WeaponSwitched(AWeapon* weapon)
{
	UTexture2D* crossHairTexture = weapon->GetCrossHairTexture();
	if (crossHairTexture) 
	{
		crossHair->SetBrushFromTexture(weapon->GetCrossHairTexture());
		crossHair->SetVisibility(ESlateVisibility::Visible);
	}
	else 
	{
		crossHair->SetVisibility(ESlateVisibility::Hidden);
	}
	weaponList->SetSelectedItem(weapon);
}

void UInGameUI::SwitchToGameOverMenu()
{
	UISwitcher->SetActiveWidgetIndex(gameOverCanvas->GetCanvasIndex());
}

void UInGameUI::SwitchToPauseMenu()
{
	UISwitcher->SetActiveWidgetIndex(pauseCanvas->GetCanvasIndex());
}

void UInGameUI::SwitchToCongratsMenu()
{
	UISwitcher->SetActiveWidget(winCanvas);

}

void UInGameUI::HideHUD()
{
	UISwitcher->GetChildAt(inGameCanvas->GetCanvasIndex())->SetVisibility(ESlateVisibility::Hidden);
}


