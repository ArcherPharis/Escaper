


#include "Gun.h"
#include "Kismet/GameplayStatics.h"

void AGun::AttackPointAnimNotify()
{
	Super::AttackPointAnimNotify();

	

	FHitResult result;
	FVector ownerViewLocation;
	FRotator ownerViewRot;
	GetOwner()->GetActorEyesViewPoint(ownerViewLocation, ownerViewRot);
	FVector Start = WeaponMesh->GetSocketLocation(MuzzleSocketName);
	if (GetWorld()->LineTraceSingleByChannel(result, Start, ownerViewLocation + ownerViewRot.Vector() * shootRange, ECC_Camera))
	{
		UE_LOG(LogTemp, Warning, TEXT("Damaging %s"), *result.GetActor()->GetName());
		UGameplayStatics::ApplyDamage(result.GetActor(), damage, nullptr, GetOwner(), nullptr);
		BP_OnBulletHit(result);
	}

	ammoInClip--;
	OnAmmoUpdated.Broadcast(ammoInClip, ammoInventory);
	if (ammoInClip == 0)
	{
		Reload();
	}

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
	GetWorldTimerManager().ClearTimer(ReloadTimerHandle); //cancels it if its active, does nothing if it's not.
}

bool AGun::GetAmmoStatus(int& clipAmmo, int& inventoryAmmo) const
{
	clipAmmo = ammoInClip;
	inventoryAmmo = ammoInventory;
	return true;
}

