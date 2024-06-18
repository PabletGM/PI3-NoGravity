// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTMoveToTarget.h"

#include "AIEnemyControllerBase.h"
#include "Navigation/PathFollowingComponent.h"

UBTTMoveToTarget::UBTTMoveToTarget()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTMoveToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::InProgress;
}

void UBTTMoveToTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIEnemyControllerBase* EnemyControllerBase = Cast<AAIEnemyControllerBase>(OwnerComp.GetOwner());

	EPathFollowingRequestResult::Type MoveToTargetResult = EnemyControllerBase->MoveToTarget();
	
	if(MoveToTargetResult == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

FString UBTTMoveToTarget::GetStaticDescription() const
{
	return TEXT("Follow Target");
}
