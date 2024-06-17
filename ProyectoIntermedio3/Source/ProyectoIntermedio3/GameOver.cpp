// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOver.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBoxSlot.h"
#include "Kismet/GameplayStatics.h"

void UGameOver::NativeConstruct()
{
	Super::NativeConstruct();

	// Bind your buttons here (optional)
}

void UGameOver::InitializeButtons()
{
	if (PlayButton)
	{
		PlayButton->OnClicked.AddDynamic(this, &UGameOver::RestartGame);
	}

	if (PlayButtonText)
	{
		PlayButtonText->SetText(FText::FromString(TEXT("Play")));
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UGameOver::QuitToMainMenu);
	}

	if (QuitButtonText)
	{
		QuitButtonText->SetText(FText::FromString(TEXT("Quit")));
	}
}

void UGameOver::ConfigureMargins()
{
	if (ButtonContainer)
	{
		UVerticalBoxSlot* PlayButtonSlot = Cast<UVerticalBoxSlot>(PlayButton->Slot);

		if (PlayButtonSlot)
		{
			PlayButtonSlot->SetPadding(FMargin(0, 0, 0, 20));
		}

		UVerticalBoxSlot* QuitButtonSlot = Cast<UVerticalBoxSlot>(QuitButton->Slot);

		if (QuitButtonSlot)
		{
			QuitButtonSlot->SetPadding(FMargin(0, 20, 0, 0));
		}
	}
}

void UGameOver::RestartGame()
{
	UGameplayStatics::OpenLevel(this, StoreLevelName);
}

void UGameOver::QuitToMainMenu()
{
	UGameplayStatics::OpenLevel(this, MainMenuLevelName);
}