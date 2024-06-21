#include "MainMenu_GameModeBase.h"

#include "GameInstanceNoGravity.h"

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

	if(ItemDataAsset)
	{
		for (int32 i = 0; i < ItemDataAsset->Items.Max(); ++i)
		{
			ItemDataAsset->Items[i].amount = 0;
		}
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("DataAsset Not found"));
}
