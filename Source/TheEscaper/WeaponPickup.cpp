// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponPickup.h"
#include "PlayerCharacter.h"
#include "Weapon.h"

AWeaponPickup::AWeaponPickup()
{
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	meshComp->SetupAttachment(GetRootComponent());
}

void AWeaponPickup::SetRandomWeapon()
{
	int randomNum = FMath::RandRange(0, weaponClasses.Num() - 1);
	weaponClass = weaponClasses[randomNum];
	meshComp->SetStaticMesh(weaponClass.GetDefaultObject()->GetMesh());
}

void AWeaponPickup::BeginPlay()
{
	Super::BeginPlay();
	if (weaponClass)
	{
		meshComp->SetStaticMesh(weaponClass.GetDefaultObject()->GetMesh());
	}
}

void AWeaponPickup::OnTriggered(AActor* actor)
{
	APlayerCharacter* playerChara = Cast<APlayerCharacter>(actor);

	if (playerChara)
	{
		playerChara->GiveWeapon(weaponClass);
		Destroy();
	}
}

void AWeaponPickup::OnActorLeftTrigger(AActor* actor)
{
}

#if WITH_EDITOR
void AWeaponPickup::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if (PropertyChangedEvent.Property)
	{
		const FName changedPropertyName = PropertyChangedEvent.GetPropertyName();
		const FName weaponClassPropertyName = GET_MEMBER_NAME_CHECKED(AWeaponPickup, weaponClass);

		if (changedPropertyName == weaponClassPropertyName)
		{
			meshComp->SetStaticMesh(weaponClass.GetDefaultObject()->GetMesh());
		}
	}
}
#endif //WITH_EDITOR
