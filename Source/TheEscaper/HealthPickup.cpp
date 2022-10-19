// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickup.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"

AHealthPickup::AHealthPickup()
{
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	meshComp->SetupAttachment(GetRootComponent());
}



void AHealthPickup::OnTriggered(AActor* actor)
{
	UGameplayStatics::ApplyDamage(actor, healAmount * -1, nullptr, this, nullptr);
	HidePickup();
}

void AHealthPickup::OnActorLeftTrigger(AActor* actor)
{
}

void AHealthPickup::UnHidePickup()
{
	meshComp->SetHiddenInGame(false);
	GetTriggerBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AHealthPickup::HidePickup()
{
	onPickup.Broadcast();
	meshComp->SetHiddenInGame(true);
	GetTriggerBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
