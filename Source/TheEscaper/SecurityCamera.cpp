// Fill out your copyright notice in the Description page of Project Settings.


#include "SecurityCamera.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Components/SpotLightComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EPlayerControler.h"

// Sets default values
ASecurityCamera::ASecurityCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	RootComponent = rootComp;

	RotationYawPivot = CreateDefaultSubobject<USceneComponent>(TEXT("RotationYawPivot"));
	RotationYawPivot->SetupAttachment(rootComp);

	RotationPitchPivot = CreateDefaultSubobject<USceneComponent>(TEXT("RotationPitchPivot"));
	RotationPitchPivot->SetupAttachment(RotationYawPivot);

	cameraLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	cameraLight->SetupAttachment(RotationPitchPivot);

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("SightConfig");
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComp");
	

	if (SightConfig && PerceptionComp)
	{
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
		SightConfig->SightRadius = 1500.f;
		SightConfig->PeripheralVisionAngleDegrees = 45.f; //angle of sight

		PerceptionComp->ConfigureSense(*SightConfig);
		PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &ASecurityCamera::PerceptionUpdated);
	}

	

}

// Called when the game starts or when spawned
void ASecurityCamera::BeginPlay()
{
	Super::BeginPlay();
	cameraLight->SetLightColor(NeutralColor);
	SightConfig->SightRadius = cameraLight->AttenuationRadius;
	SightConfig->LoseSightRadius = cameraLight->AttenuationRadius;
	SightConfig->PeripheralVisionAngleDegrees = cameraLight->OuterConeAngle;
	PerceptionComp->ConfigureSense(*SightConfig);

}



// Called every frame
void ASecurityCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASecurityCamera::SetLightColor(const FLinearColor& color)
{
	cameraLight->SetLightColor(color);
}

void ASecurityCamera::PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		cameraLight->SetLightColor(AlertColor);
		AEPlayerControler* pc = Cast<AEPlayerControler>(UGameplayStatics::GetPlayerController(this, 0));
		if (Actor->GetOwner() == pc)
		{
			pc->Caught();
			StopMoving();
		}
	}
	else
	{
		cameraLight->SetLightColor(NeutralColor);

	}
}

void ASecurityCamera::GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const
{
	OutLocation = cameraLight->GetComponentLocation();
	OutRotation = cameraLight->GetComponentRotation();

}



