// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "MovieSceneSequencePlayer.h"
#include "CinematicComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCinematicStarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCinematicStopped);


/**
 * 
 */
UCLASS()
class THEESCAPER_API UCinematicComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
	UCinematicComponent();

	FOnCinematicStarted onCinematicStarted;
	FOnCinematicStopped onCinematicStopped;

private:
	UPROPERTY(EditAnywhere, Category = "Cinematics")
	class ULevelSequence* SequenceToPlay;

	UFUNCTION()
	void Triggered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, Category = "Cinematics")
	bool bTriggerOnce = true;

	UPROPERTY(EditAnywhere, Category = "Cinematics")
	FMovieSceneSequencePlaybackSettings playSettings;

	UFUNCTION()
	void CinematicStop();
	
};
