
#include "GameOverManager.h"

#include "GameOver.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGameOverManager::AGameOverManager()
{
	PrimaryActorTick.bCanEverTick = true;
	GameOverWidget = nullptr;
}

void AGameOverManager::BeginPlay()
{
	Super::BeginPlay();
	ShowGameOverMenu();
}

void AGameOverManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGameOverManager::ShowGameOverMenu()
{
	if (GameOverMenuClass)
	{
		GameOverWidget = CreateWidget<UGameOver>(GetWorld(), GameOverMenuClass);

		if (GameOverWidget)
		{
			GameOverWidget->AddToViewport();

			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			if (PlayerController)
			{
				// Set input mode to UI only and show the cursor
				FInputModeUIOnly InputMode;
				InputMode.SetWidgetToFocus(GameOverWidget->TakeWidget());
				PlayerController->SetInputMode(InputMode);
				PlayerController->bShowMouseCursor = true;
			}
		}
	}
}

