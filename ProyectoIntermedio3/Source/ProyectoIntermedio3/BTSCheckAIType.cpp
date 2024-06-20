// Fill out your copyright notice in the Description page of Project Settings.


#include "BTSCheckAIType.h"

#include "AIEnemyControllerBase.h"

void UBTSCheckAIType::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIEnemyControllerBase* AIEnemyControllerBase = Cast<AAIEnemyControllerBase>(OwnerComp.GetOwner());

	AIEnemyControllerBase->CheckAIType();
}
