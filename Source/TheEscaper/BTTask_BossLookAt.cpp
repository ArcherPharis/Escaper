// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_BossLookAt.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Boss.h"

UBTTask_BossLookAt::UBTTask_BossLookAt()
{
	NodeName = "Boss Look At";
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_BossLookAt::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	boss = OwnerComp.GetAIOwner()->GetPawn<ABoss>();
	


	return EBTNodeResult::InProgress;
}

void UBTTask_BossLookAt::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AActor* Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BlackboardKey.SelectedKeyName));

	if (Target != nullptr && boss != nullptr)
	{
		if (boss->LookAtTargetTick(Target, DeltaSeconds))
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	
	}
	else
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

}
