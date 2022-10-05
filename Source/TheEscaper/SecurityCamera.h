// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Perception/AIPerceptionTypes.h"
#include "SecurityCamera.generated.h"

UCLASS()
class THEESCAPER_API ASecurityCamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASecurityCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "AIPerception")
	void StopMoving();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "AIPerception")
	FORCEINLINE USceneComponent* GetYawPivot() const { return RotationYawPivot; }

	UFUNCTION(BlueprintCallable, Category = "AIPerception")
	FORCEINLINE USceneComponent* GetPitchPivot() const { return RotationPitchPivot; }

	UFUNCTION(BlueprintCallable, Category = "AIPerception")
	FORCEINLINE UAIPerceptionComponent* GetPerceptionComponent() const { return PerceptionComp; }

	UFUNCTION(BlueprintCallable, Category = "AIPerception")
	void SetLightColor(const FLinearColor& color);

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "AIPerception")
	USceneComponent* rootComp;
	UPROPERTY(VisibleDefaultsOnly, Category = "AIPerception")
	USceneComponent* RotationYawPivot;
	UPROPERTY(VisibleDefaultsOnly, Category = "AIPerception")
	USceneComponent* RotationPitchPivot;
	UPROPERTY(VisibleDefaultsOnly, Category = "AIPerception")
	class USpotLightComponent* cameraLight;


	UPROPERTY(VisibleDefaultsOnly, Category = "AIPerception")
	class UAIPerceptionComponent* PerceptionComp;

	UPROPERTY()
	class UAISenseConfig_Sight* SightConfig;

	UFUNCTION()
	void PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	virtual void GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const override;

	FVector LookLocation;
	FRotator LookRotation;

	UPROPERTY(EditDefaultsOnly, Category = "AIPerception")
	FLinearColor NeutralColor {0,1,0,1};
	UPROPERTY(EditDefaultsOnly, Category = "AIPerception")
	FLinearColor AlertColor{1,0,0,1};

};
