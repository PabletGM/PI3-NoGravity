// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "AIEnemyControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class PROYECTOINTERMEDIO3_API AAIEnemyControllerBase : public AAIController
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, Category = "AI") void CheckTargetDistance();
	UFUNCTION(BlueprintCallable, Category = "AI") EPathFollowingRequestResult::Type MoveToTarget();
};
