// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUI.h"
#include "ValueGauge.h"
#include "Components/TextBlock.h"

void UInGameUI::UpdateHealth(float health, float delta, float maxHealth)
{

	healthBar->SetValue(health, delta, maxHealth);
}

void UInGameUI::UpdateAmmoText(int newValue)
{
	ammoText->SetText(FText::AsNumber(newValue));
}
