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
	void PlaySoundEffect1(USoundBase* Sound);

	// Function2 to play a sound
	UFUNCTION(BlueprintCallable, Category = "Audio")
	void PlaySoundEffect2(USoundBase* Sound);

	// Function2 to play a music
	UFUNCTION(BlueprintCallable, Category = "Audio")
	void PlayMusic(USoundBase* Sound);

	
	// Array to hold sound references
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	TArray<USoundBase*> SoundArray;

	// Function to find a sound by name
	UFUNCTION(BlueprintCallable, Category = "Audio")
	USoundBase* FindSoundByName(FString SoundName);

	UPROPERTY(EditAnywhere) float SFXVolume = 0.1f;
	UPROPERTY(EditAnywhere) float MusicVolume = 0.05f;
};
