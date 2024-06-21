// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOver.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBoxSlot.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerStateProyectoIntermedio3.h"

void UGameOver::NativeConstruct()
{
	Super::NativeConstruct();

	// Bind your buttons here (optional)
	InitializeButtons();
	this->SetVisibility(ESlateVisibility::Collapsed);
}

void UGameOver::InitializeButtons()
{
	if (PlayButton)
	{
		PlayButton->OnClicked.AddDynamic(this, &UGameOver::RestartGame);
	}

	if (PlayButtonText)
	{
		PlayButtonText->SetText(FText::FromString(TEXT("Try Again")));
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UGameOver::QuitToMainMenu);
	}

	if (QuitButtonText)
	{
		QuitButtonText->SetText(FText::FromString(TEXT("Main Menu")));
	}
}

void UGameOver::ConfigureMargins()
{
	if (ButtonContainer)
	{
		UVerticalBoxSlot* PlayButtonSlot = Cast<UVerticalBoxSlot>(PlayButton->Slot);

		if (PlayButtonSlot)
		{
			PlayButtonSlot->SetPadding(FMargin(0, 0, 0, 100));
		}

		UVerticalBoxSlot* QuitButtonSlot = Cast<UVerticalBoxSlot>(QuitButton->Slot);

		if (QuitButtonSlot)
		{
			QuitButtonSlot->SetPadding(FMargin(0, 20, 0, 200));
		}
	}
}

void UGameOver::RestartGame()
{
	APlayerStateProyectoIntermedio3* PlayerState = Cast<APlayerStateProyectoIntermedio3>(UGameplayStatics::GetPlayerState(GetWorld(), 0));
	PlayerState->UpdateWidgetPearl();
	UE_LOG(LogTemp, Warning, TEXT("RestartGame"));
	UGameplayStatics::OpenLevel(this, StoreLevelName);
}

void UGameOver::QuitToMainMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("QuitToMainMenu"));
	UGameplayStatics::OpenLevel(this, MainMenuLevelName);
}