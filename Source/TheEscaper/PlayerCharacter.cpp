// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

APlayerCharacter::APlayerCharacter()
{
	playerEye = CreateDefaultSubobject<UCameraComponent>("playerEye");
	playerEye->SetupAttachment(GetRootComponent());
	playerEye->bUsePawnControlRotation = true;
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::Jump);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &APlayerCharacter::Attack);
	PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, this, &APlayerCharacter::NextWeapon);
	PlayerInputComponent->BindAction("PreviousWeapon", IE_Pressed, this, &APlayerCharacter::PrevWeapon);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &APlayerCharacter::Reload);




}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetMesh()->AttachToComponent(playerEye, FAttachmentTransformRules::KeepWorldTransform);

}

void APlayerCharacter::MoveRight(float value)
{
	AddMovementInput(GetActorRightVector() * value);
}

void APlayerCharacter::Turn(float value)
{
	AddControllerYawInput(value);

}

void APlayerCharacter::LookUp(float value)
{
	AddControllerPitchInput(value);
}

void APlayerCharacter::MoveForward(float value)
{
	AddMovementInput(GetActorForwardVector() * value);
}

float APlayerCharacter::Caught()
{
	GetCharacterMovement()->MaxWalkSpeed = 0;
	float duration = GetMesh()->GetAnimInstance()->Montage_Play(CaughtMontage);
	return duration;
}


