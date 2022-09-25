// Fill out your copyright notice in the Description page of Project Settings.


#include "ECharacter_Base.h"
#include "Weapon.h"

// Sets default values
AECharacter_Base::AECharacter_Base()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AECharacter_Base::BeginPlay()
{
	Super::BeginPlay();
	weapon = GetWorld()->SpawnActor<AWeapon>(weaponClass);
	weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("GunHandSocket"));
	
}

// Called every frame
void AECharacter_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AECharacter_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

AWeapon* AECharacter_Base::GetCurrentWeapon()
{
	return weapon;
}


void AECharacter_Base::Attack()
{
	if (weapon && weapon->GetAttackMontage())
	{
		GetMesh()->GetAnimInstance()->Montage_Play(weapon->GetAttackMontage());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing either weapon or attack montage."));
	}

}

