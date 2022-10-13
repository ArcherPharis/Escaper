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

void AWeapon::OnAcquired(class USkeletalMeshComponent* OwnerMesh)
{
	OwnerSkeletalMesh = OwnerMesh;
	SetActorHiddenInGame(true);
	AttachToComponent(OwnerSkeletalMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocket);
	USkeletalMesh* mesh = OwnerMesh->SkeletalMesh;

	AttackMontage = ReloadMontage = nullptr;
	IdleAnim = WalkAnim = nullptr;

	if (AttackAnimMap.Contains(mesh))
		AttackMontage = AttackAnimMap[mesh];
	if (ReloadAnimMap.Contains(mesh))
		ReloadMontage = ReloadAnimMap[mesh];
	if (IdleAnimMap.Contains(mesh))
		IdleAnim = IdleAnimMap[mesh];
	if (WalkAnimMap.Contains(mesh))
		WalkAnim = WalkAnimMap[mesh];

}

void AWeapon::Attack()
{
	if (CanAttack())
	{
		GetWorldTimerManager().SetTimer(FiringTimer, 1 / fireRate, false);
		OwnerSkeletalMesh->GetAnimInstance()->Montage_Play(AttackMontage);
	}
}

void AWeapon::Reload()
{
}

void AWeapon::PutInInventory()
{
	SetActorHiddenInGame(true);
}

void AWeapon::PutInHand()
{
	SetActorHiddenInGame(false);
}

void AWeapon::GiveAmmoAsPickup()
{
}


void AWeapon::GetAnims(UAnimSequence*& Idle, UAnimSequence*& Walk, UAnimMontage*& Attack) const
{
	Idle = IdleAnim;
	Walk = WalkAnim;
	Attack = AttackMontage;
}

void AWeapon::AttackPointAnimNotify()
{
}

bool AWeapon::GetAmmoStatus(int& clipAmmo, int& inventoryAmmo) const
{
	return false;
}

bool AWeapon::CanAttack() const
{
	return !GetWorldTimerManager().IsTimerActive(FiringTimer);
}