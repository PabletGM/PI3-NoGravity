// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOver.h"
#include "Kismet/GameplayStatics.h"

void UGameOver::NativeConstruct()
{
	Super::NativeConstruct();

	// Bind your buttons here (optional)
}

void UGameOver::RestartGame()
{
	UGameplayStatics::OpenLevel(this, StoreLevelName);
}

void UGameOver::QuitToMainMenu()
{
	UGameplayStatics::OpenLevel(this, MainMenuLevelName);
}