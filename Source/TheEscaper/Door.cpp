// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "Components/BoxComponent.h"
#include "ECharacter_Base.h"

ADoor::ADoor()
{
	GetTriggerBox()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetTriggerBox()->SetCollisionResponseToChannel(ECC_Character, ECR_Overlap);

}

void ADoor::OnTriggered(AActor* actor)
{
	ActorsInTrigger++;
	SetDoorOpen(true);

}

void ADoor::OnActorLeftTrigger(AActor* actor)
{
	ActorsInTrigger--;
	if (ActorsInTrigger == 0)
	{
		SetDoorOpen(false);
	}
}
