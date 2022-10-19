// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnemyAIInterface.h"
#include "Boss.generated.h"



UCLASS()
class THEESCAPER_API ABoss : public APawn, public IEnemyAIInterface
{
	GENERATED_BODY()

		//homework spawn health regeneration in 4 corners every 2 seconds, only if there's not one there already
		// make boss spawn enemies at the enemy spawn point for every 5 seconds.
		//akter the enemy spawn so it knows the player right away and only attack the player. and they still drop stuff
		//pop a you win UI when boss dies.
		
public:
	// Sets default values for this pawn's properties
	ABoss();


	bool LookAtTargetTick(AActor* Target, float deltaTime);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Boss")
	void OnDead();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Attack();

	UFUNCTION(BlueprintCallable, Category = "Boss")
	FORCEINLINE USceneComponent* GetWheelPivot() const { return WheelPivot; }


	UFUNCTION(BlueprintCallable, Category = "Boss")
	FORCEINLINE USceneComponent* GetRotatePivot() const { return RotationPivot; }

private:
	UPROPERTY(VisibleAnywhere, Category = "Boss")
	USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere, Category = "Boss")
	USceneComponent* WheelPivot;

	UPROPERTY(VisibleAnywhere, Category = "Boss")
	USceneComponent* RotationPivot;

	UPROPERTY(VisibleAnywhere, Category = "Boss")
	USceneComponent* EnemySpawnPoint;

	UPROPERTY(VisibleAnywhere, Category = "Boss")
	class UWidgetComponent* HealthBarWidgetComp;

	UPROPERTY(VisibleAnywhere, Category = "Boss")
	class UHealthComponent* HealthComp;

	UPROPERTY(EditDefaultsOnly, Category = "Boss")
		float rotationLerpSpeed = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = "Boss")
	TSubclassOf<class AProjectile> projectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Boss")
	float ProjectileDamage = 80.f;

	UPROPERTY(EditDefaultsOnly, Category = "Boss")
	float ProjectileCoolDown = 2.f;

	class UValueGauge* HealthBar;

	TArray<class AEEnemy*> enemies;

	UFUNCTION()
	void HealthUpdated(float health, float delta, float maxHealth);

	UFUNCTION()
	void Die();

	UPROPERTY(EditDefaultsOnly, Category = "Boss")
	TSubclassOf<AEEnemy> minionToSpawnClass;

	UPROPERTY(EditDefaultsOnly, Category = "Boss")
	float enemySpawnRate = 5.f;

	void SpawnEnemies();
	void RelayDeath();

	FTimerHandle coolDownTimer;
	FTimerHandle enemySpawnTimer;

};
