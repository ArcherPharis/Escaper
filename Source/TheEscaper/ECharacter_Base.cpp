// Fill out your copyright notice in the Description page of Project Settings.


#include "ECharacter_Base.h"
#include "Components/CapsuleComponent.h"
#include "Weapon.h"
#include "HealthComponent.h"

// Sets default values
AECharacter_Base::AECharacter_Base()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->SetCollisionObjectType(ECC_Character);
	healthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	healthComp->OnHealthChanged.AddDynamic(this, &AECharacter_Base::HealthChanged);
	healthComp->OnHealthEmpty.AddDynamic(this, &AECharacter_Base::StartDeathSequence);


}

// Called when the game starts or when spawned
void AECharacter_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AECharacter_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AECharacter_Base::GiveWeapon(TSubclassOf<AWeapon> weaponClass)
{
	if (HasWeaponOfType(weaponClass))
	{
		//TODO: maybe add ammo here
		return;
	}

	AWeapon* newWeapon = GetWorld()->SpawnActor<AWeapon>(weaponClass);
	newWeapon->SetOwner(this);
	newWeapon->OnAcquired(GetMesh());
	weapons.Add(newWeapon);
	OnWeaponGiven.Broadcast(newWeapon);

	if (currentWeapon == nullptr)
	{
		EquipWeapon(weapons.Num() - 1);
	}
}

// Called to bind functionality to input
void AECharacter_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AECharacter_Base::Attack()
{
	if (currentWeapon != nullptr && !GetWorldTimerManager().IsTimerActive(WeaponSwitchingHandle))
	{
		currentWeapon->Attack();
	}
}

void AECharacter_Base::PrevWeapon()
{

	if (weapons.Num() <= 0)
		return;

	int previousIndex = weaponIndex - 1;

	if (previousIndex < 0)
	{
		previousIndex = weapons.Num() - 1;
	}
	EquipWeapon(previousIndex);

}

void AECharacter_Base::NextWeapon()
{

	if (weapons.Num() <= 0)
		return;
	int nextIndex = weaponIndex + 1;
	if (nextIndex >= weapons.Num())
	{
		nextIndex = 0;
	}
	EquipWeapon(nextIndex);
}

void AECharacter_Base::Reload()
{
	if (currentWeapon)
	{
		currentWeapon->Reload();
	}
}


bool AECharacter_Base::HasWeaponOfType(TSubclassOf<AWeapon> weaponClass) const
{
	for (AWeapon* weapon : weapons)
	{
		if (weapon->GetClass() == weaponClass)
		{
			return true;
		}
	}
	return false;
}

void AECharacter_Base::EquipWeapon(int index)
{

	if (currentWeapon == weapons[index])
	{
		return;
	}


	float SwitchDuration = GetMesh()->GetAnimInstance()->Montage_Play(WeaponSwitchMontage);
	weaponIndex = index;
	GetWorldTimerManager().SetTimer(WeaponSwitchingHandle, this, &AECharacter_Base::WeaponSwitchTimePoint, SwitchDuration / 2, false);



}

void AECharacter_Base::HealthChanged(float val, float delta, float max)
{
	OnHealthChange(val, delta, max);
}

void AECharacter_Base::StartDeathSequence()
{
	if (!bIsDead)
	{
		bIsDead = true;
		DisableGameplayRelevancy();
		OnDeathStart();

		for (auto weapon : weapons)
		{
			weapon->Destroy();
		}

		if (DeathMontage)
		{
			float deathAnimDuration = GetMesh()->GetAnimInstance()->Montage_Play(DeathMontage);
			GetWorldTimerManager().SetTimer(DeathTimerHandle, this, &AECharacter_Base::Dead, deathAnimDuration + 1, false);
		}
	}

}

void AECharacter_Base::OnHealthChange(float val, float delta, float max)
{
}

void AECharacter_Base::OnDeathStart()
{
}

void AECharacter_Base::Dead()
{


	Destroy();

}

void AECharacter_Base::DisableGameplayRelevancy()
{

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AECharacter_Base::WeaponSwitchTimePoint()
{

	if (currentWeapon)
	{
		currentWeapon->PutInInventory();
	}

	currentWeapon = weapons[weaponIndex];
	currentWeapon->PutInHand();
	OnWeaponSwitched.Broadcast(currentWeapon);

}


