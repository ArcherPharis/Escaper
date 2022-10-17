// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss.h"
#include "Components/WidgetComponent.h"
#include "ValueGauge.h"
#include "HealthComponent.h"
#include "Projectile.h"
#include "Kismet/KismetMathLibrary.h"
#include "AIController.h"
#include "BrainComponent.h"

// Sets default values
ABoss::ABoss()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);
	RotationPivot = CreateDefaultSubobject<USceneComponent>(TEXT("Rotation Pivot"));
	RotationPivot->SetupAttachment(RootComp);
	WheelPivot = CreateDefaultSubobject<USceneComponent>(TEXT("Wheel Pivot"));
	WheelPivot->SetupAttachment(RotationPivot);

	EnemySpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Enemy Spawn Point"));
	EnemySpawnPoint->SetupAttachment(RotationPivot);

	HealthBarWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("Health Bar Widget Component"));
	HealthBarWidgetComp->SetupAttachment(RootComp);

	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	HealthComp->OnHealthChanged.AddDynamic(this, &ABoss::HealthUpdated);
	HealthComp->OnHealthEmpty.AddDynamic(this, &ABoss::Die);


}

bool ABoss::LookAtTargetTick(AActor* Target, float deltaTime)
{
	FRotator currentRot = RotationPivot->GetComponentRotation();
	FRotator GoalRotation = UKismetMathLibrary::FindLookAtRotation(RotationPivot->GetComponentLocation(), Target->GetActorLocation());

	if (currentRot.Equals(GoalRotation, 1)) return true;

	RotationPivot->SetWorldRotation(FMath::Lerp(currentRot, GoalRotation, deltaTime * rotationLerpSpeed));
	return false;
}

// Called when the game starts or when spawned
void ABoss::BeginPlay()
{
	Super::BeginPlay();
	HealthBar = Cast<UValueGauge>(HealthBarWidgetComp->GetUserWidgetObject());
	
}

// Called every frame
void ABoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABoss::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
//interface
void ABoss::Attack()
{
	if (!projectileClass) return;

	if (GetWorldTimerManager().IsTimerActive(coolDownTimer))
	return;

	GetWorldTimerManager().SetTimer(coolDownTimer, ProjectileCoolDown, false);

	FVector location = WheelPivot->GetComponentLocation();
	FRotator rotation = WheelPivot->GetComponentRotation();
	AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(projectileClass, location, rotation);
	projectile->SetDamage(ProjectileDamage);
	projectile->SetOwner(this);
}

void ABoss::HealthUpdated(float health, float delta, float maxHealth)
{
	if (HealthBar)
	{
		HealthBar->SetValue(health, delta, maxHealth);
	}
}

void ABoss::Die()
{
	AAIController* AIC = GetController<AAIController>();
	if (AIC)
	{
		UBrainComponent* braincomp = AIC->GetBrainComponent();
		if (braincomp)
		{
			braincomp->StopLogic("Dead");
		}
	}
	OnDead();
	Destroy();

}

