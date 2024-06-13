// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AB_StoreDiver.generated.h"

/**
 * 
 */
UCLASS()
class PROYECTOINTERMEDIO3_API UAB_StoreDiver : public UAnimInstance
{
	GENERATED_BODY()

public:
	UAB_StoreDiver();

	// Function to update the float variable
	UFUNCTION(BlueprintCallable, Category = "Animation")
	void UpdateSpeedVariable(float NewValue);
	
	// This will be a variable exposed to Blueprints
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	float speedPlayer;
	
};
