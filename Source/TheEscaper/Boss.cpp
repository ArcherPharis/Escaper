// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss.h"
#include "Components/WidgetComponent.h"
#include "ValueGauge.h"
#include "HealthComponent.h"
#include "Projectile.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "EPlayerControler.h"
#include "EEnemy.h"
#include"CinematicComponent.h"
#include "Components/PointLightComponent.h"

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

	cinematicComp = CreateDefaultSubobject<UCinematicComponent>(TEXT("Cinematic Component"));
	cinematicComp->SetupAttachment(GetRootComponent());
	cinematicComp->onCinematicStarted.AddDynamic(this, &ABoss::CinematicStarted);
	cinematicComp->onCinematicStopped.AddDynamic(this, &ABoss::CinematicStopped);

	pointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Point Light"));
	pointLight->SetupAttachment(RotationPivot);



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
	//SetLogicEnabled(false);
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
	OnAttack();
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

	SetLogicEnabled(false);
	OnDead();
	RelayDeath();
	Destroy();
	GetWorldTimerManager().ClearTimer(enemySpawnTimer);

}

void ABoss::SpawnEnemies()
{
	AEEnemy* enemy;
	enemy = GetWorld()->SpawnActor<AEEnemy>(minionToSpawnClass, EnemySpawnPoint->GetComponentLocation(), EnemySpawnPoint->GetComponentRotation());
	enemies.Add(enemy);
	if(enemy)
	enemy->SpawnDefaultController();



}

void ABoss::RelayDeath()
{
	AEPlayerControler* playerController = Cast<AEPlayerControler>(UGameplayStatics::GetPlayerController(this, 0));
	for (AEEnemy* enemy : enemies)
	{
		AAIController* AIC = enemy->GetController<AAIController>();
		if (AIC)
		{
			UBrainComponent* braincomp = AIC->GetBrainComponent();
			if (braincomp)
			{
				braincomp->StopLogic("Our master is dead.");
				UGameplayStatics::ApplyDamage(enemy, 9999999, GetController(), this, nullptr);
			}

		}
	}
	playerController->BossDefeated();

}

void ABoss::CinematicStarted()
{
	SetLogicEnabled(false);
}

void ABoss::CinematicStopped()
{
	SetLogicEnabled(true);
	GetWorldTimerManager().SetTimer(enemySpawnTimer, this, &ABoss::SpawnEnemies, enemySpawnRate, true);


}

void ABoss::SetLogicEnabled(bool bIsLogicEnabled)
{

	AAIController* AIC = GetController<AAIController>();
	if (AIC)
	{
		UBrainComponent* braincomp = AIC->GetBrainComponent();
		if (braincomp)
		{
			if (bIsLogicEnabled)
			{
				braincomp->StartLogic();
			}
			else 
			{
				braincomp->StopLogic("Dead");
			}
			
		}
	}
}

