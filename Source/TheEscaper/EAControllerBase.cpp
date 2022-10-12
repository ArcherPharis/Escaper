// Fill out your copyright notice in the Description page of Project Settings.


#include "EAControllerBase.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AIPerceptionTypes.h"
#include "BehaviorTree/BlackboardComponent.h"

AEAControllerBase::AEAControllerBase()
{
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComp"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	DamageConfig = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("DamageConfig"));
	PerceptionComp->ConfigureSense(*SightConfig);
	PerceptionComp->ConfigureSense(*DamageConfig);
	PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AEAControllerBase::OnPerceptionUpdated);
}

void AEAControllerBase::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(behviorTree);
}

void AEAControllerBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//if (SensedActor)
	//{
	//	//GetBlackboardComponent()->GetValueAsObject(TargetBlackboardKeyName);
	//	GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), SensedActor->GetActorLocation());

	//}
	//else
	//{
	//	GetBlackboardComponent()->ClearValue(TargetBlackboardKeyName);
	//}
}

void AEAControllerBase::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		UE_LOG(LogTemp, Warning, TEXT("Seeing: %s"),* Actor->GetName());
		GetBlackboardComponent()->SetValueAsObject(TargetBlackboardKeyName, Actor);
	}
	else
	{
		const FActorPerceptionInfo* perceptionInfo = PerceptionComp->GetActorInfo(*Actor);

		if (!perceptionInfo->HasAnyCurrentStimulus())
		{
			UE_LOG(LogTemp, Warning, TEXT("He gone: %s"), *Actor->GetName());
			GetBlackboardComponent()->ClearValue(TargetBlackboardKeyName);
			GetBlackboardComponent()->SetValueAsVector(LastSeenKeyName, Actor->GetActorLocation());
		}


		
		//if ai loses track of you, ai goes to the last place it sees you first, wait for 2 seconds and then if still not seeing you,
		// go back

		//do not clear the value if there is still another sense sensing the target.

	}
}
