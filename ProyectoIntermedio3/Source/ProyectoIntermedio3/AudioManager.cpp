// Fill out your copyright notice in the Description page of Project Settings.

#include "AudioManager.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

// Called when the game starts or when spawned
AAudioManager::AAudioManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAudioManager::BeginPlay()
{
	Super::BeginPlay();

	// PlaySound(SoundArray[0]);
}

// Called every frame
void AAudioManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Function to play a sound
void AAudioManager::PlaySoundEffect1(USoundBase* Sound)
{
	if (Sound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, Sound, GetActorLocation(), SFXVolume);
	}
}

void AAudioManager::PlaySoundEffect2(USoundBase* Sound)
{
	if (Sound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, Sound, GetActorLocation(), SFXVolume);
	}
}

void AAudioManager::PlayMusic(USoundBase* Sound)
{
	if (Sound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, Sound, GetActorLocation(), MusicVolume);
	}
}

// Function to find a sound by name
USoundBase* AAudioManager::FindSoundByName(FString SoundName)
{
	for (USoundBase* Sound : SoundArray)
	{
		if (Sound && Sound->GetName() == SoundName)
		{
			return Sound;
		}
	}
	return nullptr;
}


