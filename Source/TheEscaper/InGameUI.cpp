// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUI.h"
#include "ValueGauge.h"
#include "Components/Image.h"
#include "Components/ListView.h"
#include "Weapon.h"
#include "GameMenuCanvas.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UInGameUI::NativeConstruct()
{
	Super::NativeConstruct();
	continueButton->OnReleased.AddDynamic(this, &UInGameUI::Resume);
	restartButton->OnReleased.AddDynamic(this, &UInGameUI::Restart);
	quitButton->OnReleased.AddDynamic(this, &UInGameUI::Quit);

}

void UInGameUI::Resume()
{
	//TODO, just broadcast an event that playercontroller recieves and executes all this.
	UGameplayStatics::SetGamePaused(this, false);
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(UGameplayStatics::GetPlayerController(this, 0));
	UGameplayStatics::GetPlayerController(this, 0)->SetShowMouseCursor(false);
	UISwitcher->SetActiveWidgetIndex(inGameCanvas->GetCanvasIndex());
}

void UInGameUI::Restart()
{
	UGameplayStatics::GetPlayerController(this, 0)->RestartLevel();
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(UGameplayStatics::GetPlayerController(this, 0));
}

void UInGameUI::Quit()
{
	UGameplayStatics::GetPlayerController(this, 0)->ConsoleCommand("quit");
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


