// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnHealthChange, float, health, float, delta, float, maxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthEmpty);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THEESCAPER_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();
	FOnHealthChange OnHealthChanged;
	FOnHealthEmpty OnHealthEmpty;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UFUNCTION()
	void TakenDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser);
	void ChangeHealth(float amount);

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float Health = 100.f;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float maxHealth = 100.f;
		
};
