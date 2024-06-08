#include "MainMenu_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "MainMenuWidget.h"

void AMainMenu_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);

		UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
	}

	if (MainMenuWidgetTemplate)
	{
		MainMenuWidget = CreateWidget<UMainMenuWidget>(this, MainMenuWidgetTemplate);

		if (MainMenuWidget)
		{
			MainMenuWidget->AddToViewport(0);
			bShowMouseCursor = true;
		}
	}
}
