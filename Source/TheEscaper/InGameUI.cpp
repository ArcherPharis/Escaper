// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUI.h"
#include "ValueGauge.h"
#include "Components/Image.h"
#include "Components/ListView.h"
#include "Weapon.h"

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
}
