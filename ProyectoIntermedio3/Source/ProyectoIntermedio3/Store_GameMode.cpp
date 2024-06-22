#include "Store_GameMode.h"
#include "AudioManager.h"
#include "PlayerStateProyectoIntermedio3.h"
#include "ItemStore.h"
#include "GameInstanceNoGravity.h"

AStore_GameMode::AStore_GameMode()
{
	// set default pawn class to our Blueprinted character of the store
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/_NoGravity/Blueprints/Store/BP_CharacterStore"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/_NoGravity/Blueprints/Store/Store_PlayerController"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	PlayerStateClass = APlayerStateProyectoIntermedio3::StaticClass();
}

void AStore_GameMode::BeginPlay()
{
	UGameInstanceNoGravity* GameInstance = Cast<UGameInstanceNoGravity>(GetGameInstance());

	if (GameInstance)
	{
		totalPealrsPlayer = GameInstance->GetTotalPearls();
		UE_LOG(LogTemp, Log, TEXT("Total Pearls Player initialized to %d"), totalPealrsPlayer);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to cast to UGameInstanceNoGravity"));
	}

	Super::BeginPlay();
	GetWorldTimerManager().SetTimerForNextTick(this, &AStore_GameMode::PostBeginPlay);
}


bool AStore_GameMode::CanBuyItem(AItemStore* Item)
{
	if (!Item)
	{
		return false;
	}

	int32 ItemPrice = Item->GetItemPrice();
	return totalPealrsPlayer >= ItemPrice;
}

void AStore_GameMode::BuyItem(AItemStore* Item)
{
	//if (CanBuyItem(Item))
//{
		totalPealrsPlayer -= Item->GetItemPrice();
		Item->BuyItem();
	/* }
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("0 money"));
	}*/
		//sound to buy item
		MakeSoundEffect("buyItem");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("0 money"));
		//sound to not buy item
		MakeSoundEffect("errorBuying");
	}
}

void AStore_GameMode::InitializeAudioManager()
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

void AStore_GameMode::MakeMusic(FString nameMusic)
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

void AStore_GameMode::MakeSoundEffect(FString nameSound)
{
	if (AudioManagerInstance)
	{
		// Example method call on AudioManagerInstance
		// Replace PlaySound with your actual method name and parameters
		USoundBase* Sound1 = AudioManagerInstance->FindSoundByName(nameSound);
		if (Sound1)
		{
			AudioManagerInstance->PlaySoundEffect1(Sound1);
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


void AStore_GameMode::PostBeginPlay()
{
	InitializeAudioManager();
	MakeMusic("mainMenuMusic");
}


