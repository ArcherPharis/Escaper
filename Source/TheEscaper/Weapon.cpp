// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComp = CreateDefaultSubobject<USceneComponent>("RootComp");
	SetRootComponent(RootComp);
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMesh");
	WeaponMesh->SetupAttachment(RootComp);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponMesh->SetMobility(EComponentMobility::Movable);

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::SetCanFire(bool bCanFire)
{
	canFire = bCanFire;
}

void AWeapon::OnAcquired(USkeletalMeshComponent* ownerMeshComponent)
{
	OwnerSkeletalMesh = ownerMeshComponent;
	SetActorHiddenInGame(true);
	AttachToComponent(OwnerSkeletalMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocket);

}

void AWeapon::Attack()
{
	if (canFire) {
		canFire = false;
		OwnerSkeletalMesh->GetAnimInstance()->Montage_Play(AttackMontage);
		FTimerHandle FireRateHandle;
		GetWorldTimerManager().SetTimer(FireRateHandle, this, &AWeapon::CanFire, 1/fireRate);
	}

}

void AWeapon::GetAnims(UAnimSequence*& Idle, UAnimSequence*& Walk, UAnimMontage*& Attack) const
{

	Idle = IdleAnim;
	Walk = WalkAnim;
	Attack = AttackMontage;
}

void AWeapon::AttackPointAnimNotify()
{

	UE_LOG(LogTemp, Warning, TEXT("Commiting attack!!!!!!!!!!!!!"));
}

void AWeapon::ReloadAnimNotify()
{
}

void AWeapon::ReloadWeapon()
{
}

USkeletalMeshComponent* AWeapon::GetSkeletalMesh() const
{
	return OwnerSkeletalMesh;
}

void AWeapon::CanFire()
{
	canFire = true;
}



