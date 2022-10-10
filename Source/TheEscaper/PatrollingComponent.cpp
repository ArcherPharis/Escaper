// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrollingComponent.h"




ATargetPoint* UPatrollingComponent::GetNextPatrolPoint()
{
	if (PatrolPoints.Num() > 0)
	{
		++currentPatrolIndex;
		if (currentPatrolIndex >= PatrolPoints.Num())
		{
			currentPatrolIndex = 0;
		}
		return PatrolPoints[currentPatrolIndex];
	}
	return nullptr;
}

