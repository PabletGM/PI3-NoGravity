// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TeleportInstance.generated.h"

UCLASS()
class PROYECTOINTERMEDIO3_API ATeleportInstance : public AActor
{
	GENERATED_BODY()

public:    
	ATeleportInstance();

private:
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UBoxComponent* CollisionBox;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	FName LevelName;
};
