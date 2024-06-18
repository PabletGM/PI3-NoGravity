#include "MainMenu_GameModeBase.h"
#include "MainMenu_PlayerController.h"

AMainMenu_GameModeBase::AMainMenu_GameModeBase()
	: Super()
{
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/_NoGravity/Blueprints/BP_MainMenuPlayerController"));
	
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}
