// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AB_GameDiver.generated.h"

/**
 * 
 */
UCLASS()
class PROYECTOINTERMEDIO3_API UAB_GameDiver : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UAB_GameDiver();

	// Function to update the float variable
	UFUNCTION(BlueprintCallable, Category = "Animation")
	void Death();

	
	
	// This will be a variable exposed to Blueprints
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	bool bIsDead = false;
};
