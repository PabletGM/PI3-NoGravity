// Fill out your copyright notice in the Description page of Project Settings.

#include "AudioManager.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

AAudioManager* AAudioManager::Instance = nullptr;

// Sets default values
AAudioManager::AAudioManager()
{
	PrimaryActorTick.bCanEverTick = true;
	if (Instance)
	{
		Destroy();
	}
	else
	{
		Instance = this;
		SetLifeSpan(0.0f); // 0 means it will not be destroyed automatically
	}
}

// Called when the game starts or when spawned
void AAudioManager::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("AudioManager initialized"));
}

// Called every frame
void AAudioManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAudioManager::PlaySound(USoundBase* Sound)
{
	if (Sound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, Sound, GetActorLocation());
	}
}

void AAudioManager::BeginDestroy()
{
	if (Instance == this)
	{
		Instance = nullptr;
	}
	Super::BeginDestroy();
	// Prevent this actor from being destroyed
	SetLifeSpan(0.0f);
}

