
#include "Gun.h"
#include "Kismet/GameplayStatics.h"

void AGun::BeginPlay()
{
	Super::BeginPlay();
	ammo = maxAmmo;

	FTimerHandle FireRateHandle;
	GetWorldTimerManager().SetTimer(FireRateHandle, this, &AGun::SetInitialAmmo, 0.01f, false);
	
	
	
}

void AGun::CanFire()
{
	if (ammo >= 1)
	{
		SetCanFire(true);
	}
	else
	{
		SetCanFire(false);
	}

}

void AGun::ReloadWeapon()
{
	if (ammo <= maxAmmo && ammo != maxAmmo)
	{

		if(reloadMontage)
		GetSkeletalMesh()->GetAnimInstance()->Montage_Play(reloadMontage);

	}

}

void AGun::Attack()
{
	Super::Attack();
	if (ammo == 0)
	{
		ReloadWeapon();
	}
}


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

		if (ammo >= 1)
		{
			UE_LOG(LogTemp, Warning, TEXT("Damaging %s"), *result.GetActor()->GetName());
			UGameplayStatics::ApplyDamage(result.GetActor(), damage, nullptr, GetOwner(), nullptr);
			ammo = FMath::Clamp(ammo - 1, 0, maxAmmo);
			onAmmoChange.Broadcast(ammo);
		}

	}

}

void AGun::ReloadAnimNotify()
{
	ammo = maxAmmo;
	SetCanFire(true);
	onAmmoChange.Broadcast(ammo);
}

void AGun::SetInitialAmmo()
{
	onAmmoChange.Broadcast(ammo);
}
