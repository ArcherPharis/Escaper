// Fill out your copyright notice in the Description page of Project Settings.


#include "EAControllerBase.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AIPerceptionTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ECharacter_Base.h"
#include "Kismet/GameplayStatics.h"



AEAControllerBase::AEAControllerBase()
{
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComp"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	DamageConfig = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("DamageConfig"));
	PerceptionComp->ConfigureSense(*SightConfig);
	PerceptionComp->ConfigureSense(*DamageConfig);
	PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AEAControllerBase::OnPerceptionUpdated);
}

ETeamAttitude::Type AEAControllerBase::GetTeamAttitudeTowards(const AActor& Other) const
{
	
	const APawn* pawn = Cast<APawn>(&Other);

	if (!pawn) 
		return ETeamAttitude::Neutral;

	auto pTI = Cast<IGenericTeamAgentInterface>(&Other);
	class IGenericTeamAgentInterface* bTI = Cast<IGenericTeamAgentInterface>(pawn->GetController());
	if (bTI == nullptr && pTI == nullptr)
		return ETeamAttitude::Neutral;


	FGenericTeamId otherID = NULL;
	if (bTI != nullptr)
	{
		otherID = bTI->GetGenericTeamId();
	}
	else if (pTI != nullptr)
	{
		otherID = pTI->GetGenericTeamId();
	}

	if (otherID == 20)
	{
		return ETeamAttitude::Neutral;
	}
	else if (otherID == TeamID)
	{
		return ETeamAttitude::Friendly;
	}
	else
	{
		return ETeamAttitude::Hostile;
	}


}

void AEAControllerBase::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(behviorTree);
	GetBlackboardComponent()->SetValueAsObject(PlayerKeyName, UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	AECharacter_Base* chara = Cast<AECharacter_Base>(GetPawn());
	if (chara)
	{
		TeamID = FGenericTeamId(chara->GetGenericTeamId());
	}
}

void AEAControllerBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

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
