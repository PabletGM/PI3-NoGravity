// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTRandomMovement.h"
#include "AIEnemyControllerBase.h"
#include "Logging/StructuredLog.h"
#include "Navigation/PathFollowingComponent.h"

UBTTRandomMovement::UBTTRandomMovement()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTRandomMovement::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UE_LOGFMT(LogTemp, Log, "Random Movement");
	return EBTNodeResult::InProgress;
}

void UBTTRandomMovement::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIEnemyControllerBase* AIEnemyControllerBase = Cast<AAIEnemyControllerBase>(OwnerComp.GetOwner());

	EPathFollowingRequestResult::Type MoveToRandomResult = AIEnemyControllerBase->MoveRandom();
	
	if(MoveToRandomResult == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

FString UBTTRandomMovement::GetStaticDescription() const
{
	return TEXT("Move Randomly");
}
