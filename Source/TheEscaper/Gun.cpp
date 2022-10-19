#include "Gun.h"
#include "kismet/GameplayStatics.h"
#include "Perception/AISense_Damage.h"

void AGun::AttackPointAnimNotify()
{
	Super::AttackPointAnimNotify();

		FHitResult result;
		FVector ownerViewLoc;
		FRotator ownerViewRot;
		GetOwner()->GetActorEyesViewPoint(ownerViewLoc, ownerViewRot);
		FVector Start = WeaponMesh->GetSocketLocation(MuzzleSocketName);
		if (GetWorld()->LineTraceSingleByChannel(result, Start, ownerViewLoc + ownerViewRot.Vector() * shootRange, ECC_Camera))
		{
			UGameplayStatics::ApplyDamage(result.GetActor(), GetWeaponDamage(), nullptr, GetOwner(), nullptr);
			
			BP_OnBulletHit(result);
		}


		DecrementAmmo();
}


void AGun::Reload()
{
	if (IsReloading() || ammoInClip >= clipCapacity) return;

	float reloadDuration = GetOwnerSkeletalMesh()->GetAnimInstance()->Montage_Play(ReloadMontage);
	GetWorldTimerManager().SetTimer(ReloadTimerHandle, this, &AGun::ReloadTimePoint, reloadDuration, false);
}

bool AGun::IsReloading() const
{
	return GetOwnerSkeletalMesh()->GetAnimInstance()->Montage_IsPlaying(ReloadMontage);
}

void AGun::ReloadTimePoint()
{
	int ammoNeeded = clipCapacity - ammoInClip;
	if (ammoNeeded > ammoInventory)
	{
		ammoNeeded = ammoInventory;
	}

	ammoInventory -= ammoNeeded;
	ammoInClip += ammoNeeded;
	OnAmmoUpdated.Broadcast(ammoInClip, ammoInventory);
}

void AGun::PutInInventory()
{
	Super::PutInInventory();
	GetWorldTimerManager().ClearTimer(ReloadTimerHandle);
}

bool AGun::GetAmmoStatus(int& clipAmmo, int& inventoryAmmo) const
{
	clipAmmo = ammoInClip;
	inventoryAmmo = ammoInventory;
	return true;
}

void AGun::DecrementAmmo()
{
	ammoInClip--;
	OnAmmoUpdated.Broadcast(ammoInClip, ammoInventory);
	if (ammoInClip == 0 && ammoInventory != 0)
	{
		Reload();
	}
}

bool AGun::CanAttack() const
{
	if (IsReloading() || ammoInClip == 0) return false;

	return Super::CanAttack();
}

void AGun::GiveAmmoAsPickup()
{
	ammoInventory += ammoToGive;
	OnAmmoUpdated.Broadcast(ammoInClip, ammoInventory);
}
