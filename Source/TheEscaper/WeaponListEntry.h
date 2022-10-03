// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "WeaponListEntry.generated.h"

/**
 * 
 */
UCLASS()
class THEESCAPER_API UWeaponListEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

private:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject); //calls when you add an item



	UPROPERTY(meta = (BindWidget))
	class UImage* weaponIcon;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ammoText;

	UFUNCTION()
	void UpdateAmmo(int ammoInClip, int ammoInInventory);
};
