// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTDeath.h"

#include "AIEnemyControllerBase.h"

EBTNodeResult::Type UBTTDeath::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIEnemyControllerBase* AIEnemyControllerBase = Cast<AAIEnemyControllerBase>(OwnerComp.GetOwner());

	AIEnemyControllerBase->Death();

	return EBTNodeResult::Succeeded;
}

FString UBTTDeath::GetStaticDescription() const
{
	return TEXT("AI Death");
}
