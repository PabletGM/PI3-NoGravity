// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AB_EnemyPiranha.generated.h"

/**
 * 
 */
UCLASS()
class PROYECTOINTERMEDIO3_API UAB_EnemyPiranha : public UAnimInstance
{
	GENERATED_BODY()

public:
	UAB_EnemyPiranha();

	// Function to update the float variable
	UFUNCTION(BlueprintCallable, Category = "Animation")
	void Death();
		
	// This will be a variable exposed to Blueprints
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	bool bIsDead = false;
};
