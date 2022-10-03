// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponListEntry.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Weapon.h"

void UWeaponListEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject); //can't use super, use the interface.
	AWeapon* weapon = GetListItem<AWeapon>();
	weaponIcon->SetBrushFromTexture(GetListItem<AWeapon>()->GetWeaponIcon());
	int ammoInCLip, ammoInInventory;
	if (weapon->GetAmmoStatus(ammoInCLip, ammoInInventory))
	{
		ammoText->SetText(FText::FromString(FString::FromInt(ammoInCLip) + "/" + FString::FromInt(ammoInInventory)));
	}
	else
	{
		ammoText->SetVisibility(ESlateVisibility::Hidden);
	}
	weapon->OnAmmoUpdated.AddDynamic(this, &UWeaponListEntry::UpdateAmmo);
}

void UWeaponListEntry::UpdateAmmo(int ammoInClip, int ammoInInventory)
{
	ammoText->SetText(FText::FromString(FString::FromInt(ammoInClip) + "/" + FString::FromInt(ammoInInventory)));
}
