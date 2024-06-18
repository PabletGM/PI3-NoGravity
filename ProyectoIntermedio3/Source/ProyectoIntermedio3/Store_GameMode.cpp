#include "Store_GameMode.h"
#include "PlayerStateProyectoIntermedio3.h"
#include "ItemStore.h"
#include "GameInstanceNoGravity.h"

AStore_GameMode::AStore_GameMode()
{
	// set default pawn class to our Blueprinted character of the store
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_CharacterStore"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/ThirdPerson/Blueprints/Store_PlayerController"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	PlayerStateClass = APlayerStateProyectoIntermedio3::StaticClass();
}

void AStore_GameMode::BuyItem(AItemStore* Item)
{
	UGameInstanceNoGravity* GameInstance = Cast<UGameInstanceNoGravity>(GetGameInstance());
	if (GameInstance)
	{
		if (GameInstance->GetTotalPearls() >= Item->GetItemPrice())
		{
			GameInstance->SetTotalPearls(GameInstance->GetTotalPearls() - Item->GetItemPrice());

			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("You bought %s!"), *Item->GetItemName()));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("0 money"));
		}
	}
}
