#include "Proyecto3PlayerController.h"
#include <EnhancedInputSubsystems.h>
#include "MainWidget.h"

void AProyecto3PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);

		UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
	}

	if (MainWidgetTemplate)
	{
		MainWidget = CreateWidget<UMainWidget>(this, MainWidgetTemplate);

		if (MainWidget)
		{
			MainWidget->ShowAllWidgets();
			MainWidget->AddToViewport();
			bShowMouseCursor = false;
		}
	}
}