// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "EAControllerBase.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "ECharacter_Base.h"

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIC = OwnerComp.GetAIOwner();
	AECharacter_Base* character = AIC->GetPawn<AECharacter_Base>();
	character->Attack();

	return EBTNodeResult::Succeeded;

}
