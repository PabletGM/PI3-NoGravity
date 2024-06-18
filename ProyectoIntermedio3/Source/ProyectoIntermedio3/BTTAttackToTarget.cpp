// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTAttackToTarget.h"

#include "AIEnemyControllerBase.h"

EBTNodeResult::Type UBTTAttackToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIEnemyControllerBase* AIEnemyControllerBase = Cast<AAIEnemyControllerBase>(OwnerComp.GetOwner());

	AIEnemyControllerBase->AttackTarget();

	return EBTNodeResult::Succeeded;
}

FString UBTTAttackToTarget::GetStaticDescription() const
{
	return TEXT("Attack Target");
}
