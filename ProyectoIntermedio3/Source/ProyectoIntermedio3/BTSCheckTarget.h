// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"

#include "BTSCheckTarget.generated.h"

/**
 * 
 */
UCLASS()
class PROYECTOINTERMEDIO3_API UBTSCheckTarget : public UBTService
{
	GENERATED_BODY()

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
