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
	if (CanBuyItem(Item))
	{
		totalPealrsPlayer -= Item->GetItemPrice();
		Item->BuyItem();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("0 money"));
	}
}

void AStore_GameMode::InitializeAudioManager()
{
	// if (BP_AudioManager)
	// {
	// 	// Spawn the AudioManager instance
	// 	AudioManagerInstance = GetWorld()->SpawnActor<AAudioManager>(BP_AudioManager);
	//
	// 	if (!AudioManagerInstance)
	// 	{
	// 			UE_LOG(LogTemp, Warning, TEXT("Failed to spawn AudioManager instance!"));
	// 	}
	// }
	// else
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("BP_AudioManager is not set!"));
	// }
}
