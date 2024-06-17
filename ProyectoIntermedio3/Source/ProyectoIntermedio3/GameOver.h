// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOver.generated.h"

/**
 * 
 */
UCLASS()
class PROYECTOINTERMEDIO3_API UGameOver : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	void InitializeButtons();

	void ConfigureMargins();

	

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* GameTitleText = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* ButtonContainer = nullptr;

	//Buttons
	UPROPERTY(meta = (BindWidget))
	class UButton* PlayButton = nullptr;
	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton = nullptr;

	//Text Buttons
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PlayButtonText = nullptr;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* QuitButtonText = nullptr;

public:

	//functions clicked buttons
	UFUNCTION(BlueprintCallable, Category="GameOver")
	void RestartGame();

	UFUNCTION(BlueprintCallable, Category="GameOver")
	void QuitToMainMenu();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	FName StoreLevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	FName MainMenuLevelName;


};

