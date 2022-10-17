// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "EAControllerBase.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "ECharacter_Base.h"
#include "EnemyAIInterface.h"

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIC = OwnerComp.GetAIOwner();
	IEnemyAIInterface* AIInterface = AIC->GetPawn<IEnemyAIInterface>();
	

	if (AIInterface)
	{
		AIInterface->Attack();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;

	

}
