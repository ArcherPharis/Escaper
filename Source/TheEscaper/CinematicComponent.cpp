// Fill out your copyright notice in the Description page of Project Settings.


#include "CinematicComponent.h"
#include "LevelSequence/public/LevelSequencePlayer.h"
#include "LevelSequence/public/LevelSequenceActor.h"
#include "Kismet/GameplayStatics.h"
#include "EPlayerControler.h"


UCinematicComponent::UCinematicComponent()
{

	OnComponentBeginOverlap.AddDynamic(this, &UCinematicComponent::Triggered);
}

void UCinematicComponent::Triggered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	APawn* pawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (OtherActor != pawn) return;

	if (bTriggerOnce)
	{
		OnComponentBeginOverlap.RemoveAll(this);
	}



	if (SequenceToPlay != nullptr)
	{
		AEPlayerControler* pc = pawn->GetController<AEPlayerControler>();

		if (pc)
		{
			pc->SetUIHidden(true);
		}

		pawn->DisableInput(pawn->GetController<APlayerController>());
		UGameplayStatics::GetPlayerPawn(this, 0);

		ALevelSequenceActor* sequenceActor;
		ULevelSequencePlayer::CreateLevelSequencePlayer(this, SequenceToPlay, playSettings, sequenceActor);


		if (sequenceActor && pc)
		{
			sequenceActor->SequencePlayer->Play();
			onCinematicStarted.Broadcast();
			pc->PlayBossMusic();
			sequenceActor->SequencePlayer->OnStop.AddDynamic(this, &UCinematicComponent::CinematicStop);


		}
	}
}

void UCinematicComponent::CinematicStop()
{
	APawn* pawn = UGameplayStatics::GetPlayerPawn(this, 0);
	AEPlayerControler* pc = pawn->GetController<AEPlayerControler>();

	if (pc)
	{
		pc->SetUIHidden(false);
	}
	pawn->EnableInput(pawn->GetController<APlayerController>());
	onCinematicStopped.Broadcast();


}
