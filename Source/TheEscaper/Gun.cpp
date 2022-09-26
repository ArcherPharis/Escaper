


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
	}

}
