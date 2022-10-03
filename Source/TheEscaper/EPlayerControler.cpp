// Fill out your copyright notice in the Description page of Project Settings.


#include "EPlayerControler.h"
#include "PlayerCharacter.h"
#include "HealthComponent.h"
#include "InGameUI.h"

void AEPlayerControler::OnPossess(APawn* newPawn) //happens every time something posseses, not just at start.
{
	Super::OnPossess(newPawn);
	playerCharacter = Cast<APlayerCharacter>(newPawn);
	if (playerCharacter)
	{
		SetViewTarget(playerCharacter);
		playerCharacter->GetHealthComp()->OnHealthEmpty.AddDynamic(this, &AEPlayerControler::PawnDead);

		if (inGameUIClass)
		{
			inGameUI = CreateWidget<UInGameUI>(this, inGameUIClass);
			inGameUI->AddToViewport();
			playerCharacter->GetHealthComp()->OnHealthChanged.AddDynamic(inGameUI, &UInGameUI::UpdateHealth);
			playerCharacter->OnWeaponGiven.AddDynamic(inGameUI, &UInGameUI::NewWeaponGiven);
			playerCharacter->OnWeaponSwitched.AddDynamic(inGameUI, &UInGameUI::WeaponSwitched);

		}
	}
	else
	{
		SetViewTargetWithBlend(newPawn, 1.f);
	}


}

AEPlayerControler::AEPlayerControler()
{
	bAutoManageActiveCameraTarget = false;
}

void AEPlayerControler::PawnDead()
{
	playerCharacter->SetActorHiddenInGame(true);
	SetInputMode(FInputModeUIOnly());
	APawn* DeathPawn = GetWorld()->SpawnActor<APawn>(deathPawnClass, playerCharacter->GetTransform());
	Possess(DeathPawn);

}
