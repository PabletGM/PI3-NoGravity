// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AIEnemyBaseAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class PROYECTOINTERMEDIO3_API UAIEnemyBaseAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
