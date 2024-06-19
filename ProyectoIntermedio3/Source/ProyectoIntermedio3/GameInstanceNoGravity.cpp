#include "GameInstanceNoGravity.h"
#include "GameInstanceNoGravity.h"

#include "AudioManager.h"
#include "Kismet/GameplayStatics.h"

UGameInstanceNoGravity::UGameInstanceNoGravity()
{
	TotalPearls = 0;

	
}



void UGameInstanceNoGravity::SetTotalPearls(int32 Value)
{
	TotalPearls = Value;
}


void UGameInstanceNoGravity::Init()
{
	Super::Init();
	InitializeAudioManager();
}

void UGameInstanceNoGravity::InitializeAudioManager()
{

		// // Spawn the AudioManager Blueprint if it doesn't exist already
		// UClass* AudioManagerBPClass = LoadObject<UClass>(nullptr, TEXT("/Game/_NoGravity/Blueprints/BP_AudioManager"));
		// if (!UGameplayStatics::GetActorOfClass(GetWorld(), AAudioManager::StaticClass()))
		// {
		// 	// Spawn the AudioManager if it doesn't exist already
		// 	GetWorld()->SpawnActor<AAudioManager>(AAudioManager::StaticClass());
		// }
	
}


