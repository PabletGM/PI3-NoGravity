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

public:
	UFUNCTION(BlueprintCallable, Category="GameOver")
	void RestartGame();

	UFUNCTION(BlueprintCallable, Category="GameOver")
	void QuitToMainMenu();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	FName StoreLevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	FName MainMenuLevelName;

protected:
	virtual void NativeConstruct() override;
};

