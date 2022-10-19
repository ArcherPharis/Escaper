// Fill out your copyright notice in the Description page of Project Settings.


#include "EPlayerControler.h"
#include "PlayerCharacter.h"
#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
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
			inGameUI->OnGameResumed.AddDynamic(this, &AEPlayerControler::ResumeGame);
			inGameUI->OnGameRestarted.AddDynamic(this, &AEPlayerControler::RestartGame);
			inGameUI->OnGameQuit.AddDynamic(this, &AEPlayerControler::QuitGame);



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

void AEPlayerControler::CaughtFinished()
{
	inGameUI->SwitchToGameOverMenu();
}

void AEPlayerControler::AfterPlayerDeath()
{
	inGameUI->SwitchToGameOverMenu();
}

void AEPlayerControler::PawnDead()
{
	GetWorldTimerManager().SetTimer(DeathTimerHandle, this, &AEPlayerControler::AfterPlayerDeath, afterDeathMenuTime, false);
	inGameUI->HideHUD();
	playerCharacter->SetActorHiddenInGame(true);
	SetInputMode(FInputModeUIOnly());
	SetShowMouseCursor(true);
	APawn* DeathPawn = GetWorld()->SpawnActor<APawn>(deathPawnClass, playerCharacter->GetTransform());
	Possess(DeathPawn);

}

void AEPlayerControler::ResumeGame()
{
	
	UGameplayStatics::SetGamePaused(this, false);
	SetInputMode(FInputModeGameOnly());
	SetShowMouseCursor(false);
}

void AEPlayerControler::RestartGame()
{
	RestartLevel();
	SetInputMode(FInputModeGameOnly());

}

void AEPlayerControler::Caught()
{

	if (bIsCaught) return;

	bIsCaught = true;
	if (GetWorldTimerManager().IsTimerActive(CaughtTimerHandle)) return;
	float caughtDuration = playerCharacter->Caught();
	SetInputMode(FInputModeUIOnly());
	GetWorldTimerManager().SetTimer(CaughtTimerHandle, this, &AEPlayerControler:: CaughtFinished, caughtDuration, false);
	inGameUI->SwitchToGameOverMenu();
}

void AEPlayerControler::PauseGame()
{
	inGameUI->SwitchToPauseMenu();
	SetInputMode(FInputModeUIOnly());
	SetShowMouseCursor(true);
	UGameplayStatics::SetGamePaused(this, true);
}

void AEPlayerControler::QuitGame()
{
	UGameplayStatics::GetPlayerController(this, 0)->ConsoleCommand("quit");

}

void AEPlayerControler::BossDefeated()
{

	GetWorldTimerManager().SetTimer(PauseTimerHandle, this, &AEPlayerControler::DelayPause, pauseDelay, false);
}

void AEPlayerControler::DelayPause()
{
	inGameUI->SwitchToCongratsMenu();
	SetInputMode(FInputModeUIOnly());
	SetShowMouseCursor(true);
	UGameplayStatics::SetGamePaused(this, true);

}


