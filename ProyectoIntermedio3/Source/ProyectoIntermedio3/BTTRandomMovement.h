// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTRandomMovement.generated.h"

/**
 * 
 */
UCLASS()
class PROYECTOINTERMEDIO3_API UBTTRandomMovement : public UBTTaskNode
{
	GENERATED_BODY()

	UBTTRandomMovement();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual FString GetStaticDescription() const override;
};