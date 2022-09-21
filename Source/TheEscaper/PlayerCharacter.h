// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ECharacter_Base.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class THEESCAPER_API APlayerCharacter : public AECharacter_Base
{
	GENERATED_BODY()
public:

	APlayerCharacter();


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;

private:
	void MoveForward(float value);
	void MoveRight(float value);
	void Turn(float value);
	void LookUp(float value);
	

	UPROPERTY(VisibleDefaultsOnly, Category = "Player")
	class UCameraComponent* playerEye;
	
};
