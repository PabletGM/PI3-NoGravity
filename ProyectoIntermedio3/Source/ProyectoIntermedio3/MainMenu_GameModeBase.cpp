#include "MainMenu_GameModeBase.h"
#include "GameInstanceNoGravity.h"
#include <Kismet/GameplayStatics.h>

AMainMenu_GameModeBase::AMainMenu_GameModeBase()
	: Super()
{
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/_NoGravity/Blueprints/BP_MainMenuPlayerController"));
	
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}

void AMainMenu_GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	UGameInstanceNoGravity* GameInstance = Cast<UGameInstanceNoGravity>(UGameplayStatics::GetGameInstance(GetWorld()));

	if(ItemDataAsset)
	{
		GameInstance->ItemDataAsset = ItemDataAsset;

		for (int32 i = 0; i < ItemDataAsset->Items.Max(); ++i)
		{
			ItemDataAsset->Items[i].amount = 0;

		}
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("DataAsset Not found"));

	if (PlayerDataAsset)
	{
		GameInstance->PlayerDataAsset = PlayerDataAsset;

		ResetPlayer();
		
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("PlayarDataAsset Not found"));

	GetWorldTimerManager().SetTimerForNextTick(this, &AMainMenu_GameModeBase::PostBeginPlay);
}


void AMainMenu_GameModeBase::MakeMusic(FString nameMusic)
{
		
	if (AudioManagerInstance)
	{
		// Example method call on AudioManagerInstance
		// Replace PlaySound with your actual method name and parameters
		USoundBase* Sound2 = AudioManagerInstance->FindSoundByName(nameMusic);
		if (Sound2)
		{
			AudioManagerInstance->PlayMusic(Sound2);
		}
		else
		{
			// UE_LOG(LogTemp, Warning, TEXT("Sound not found in AudioManager!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AudioManager instance is null!"));
	}
}

void AMainMenu_GameModeBase::MakeSoundEffect1(FString nameSound)
{
	if (AudioManagerInstance)
	{
		// Example method call on AudioManagerInstance
		// Replace PlaySound with your actual method name and parameters
		USoundBase* Sound = AudioManagerInstance->FindSoundByName(nameSound);
		if (Sound)
		{
			AudioManagerInstance->PlaySoundEffect1(Sound);
		}
		else
		{
			// UE_LOG(LogTemp, Warning, TEXT("Sound not found in AudioManager!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AudioManager instance is null!"));
	}
}

void AMainMenu_GameModeBase::InitializeAudioManager()
{
	if (BP_AudioManager)
	{
		// Spawn the AudioManager instance
		AudioManagerInstance = GetWorld()->SpawnActor<AAudioManager>(BP_AudioManager);

		//add a tag to the AudioManager
		if (AudioManagerInstance)
		{
			// Assign a unique tag to the AudioManager instance
			AudioManagerInstance->Tags.Add(FName("AudioManager"));
		}
		
		if (!AudioManagerInstance)
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to spawn AudioManager instance!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("BP_AudioManager is not set!"));
	}
}

void AMainMenu_GameModeBase::PostBeginPlay()
{
	InitializeAudioManager();
	MakeMusic("musicOcean");
}

void AMainMenu_GameModeBase::ResetPlayer()
{
	PlayerDataAsset->PlayerData.MaxWalkSpeed = 500.0f;
	PlayerDataAsset->PlayerData.PlayerLevel = 1;
	PlayerDataAsset->PlayerData.MaxOxygen = 100;
	PlayerDataAsset->PlayerData.OxygenDecrement = 0.5f;
	PlayerDataAsset->PlayerData.CapacityInventory = 6;
}

