// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTRandomMovement.h"
#include "AIEnemyControllerBase.h"

EBTNodeResult::Type UBTTRandomMovement::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIEnemyControllerBase* AIEnemyControllerBase = Cast<AAIEnemyControllerBase>(OwnerComp.GetOwner());

	AIEnemyControllerBase->MoveRandom();

	return EBTNodeResult::Succeeded;
}

FString UBTTRandomMovement::GetStaticDescription() const
{
	return TEXT("Move Randomly");
}
