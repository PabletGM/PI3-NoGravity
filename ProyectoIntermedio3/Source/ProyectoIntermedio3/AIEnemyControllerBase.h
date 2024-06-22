// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NavigationSystem.h"

#include "AIEnemyControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class PROYECTOINTERMEDIO3_API AAIEnemyControllerBase : public AAIController
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "AI") void Initialize();
	UFUNCTION(BlueprintCallable, Category = "AI") void CheckIsAlive();
	UFUNCTION(BlueprintCallable, Category = "AI") void CheckTarget();
	UFUNCTION(BlueprintCallable, Category = "AI") void CheckAIType();
	UFUNCTION(BlueprintCallable, Category = "AI") void CheckTargetDistance();
	UFUNCTION(BlueprintCallable, Category = "AI") EPathFollowingRequestResult::Type MoveToTarget();
	UFUNCTION(BlueprintCallable, Category = "AI") EPathFollowingRequestResult::Type MoveRandom();
	UFUNCTION(BlueprintCallable, Category = "AI") void AttackTarget();
	UFUNCTION(BlueprintCallable, Category = "AI") void Death();
private:
	UNavigationSystemV1* NavSystem = nullptr;
};
