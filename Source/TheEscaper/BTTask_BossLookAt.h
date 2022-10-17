// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_BossLookAt.generated.h"

/**
 * 
 */
UCLASS()
class THEESCAPER_API UBTTask_BossLookAt : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_BossLookAt();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	class ABoss* boss;
	
};
