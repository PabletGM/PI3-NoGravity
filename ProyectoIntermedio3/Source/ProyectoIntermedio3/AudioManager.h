// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AudioManager.generated.h"

UCLASS()
class PROYECTOINTERMEDIO3_API AAudioManager : public AActor
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AAudioManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Function to play a sound
	UFUNCTION(BlueprintCallable, Category = "Audio")
	void PlaySound(USoundBase* Sound);

	// Ensure this actor is not destroyed when loading new levels
	virtual void BeginDestroy() override;

private:
	static AAudioManager* Instance;
};
