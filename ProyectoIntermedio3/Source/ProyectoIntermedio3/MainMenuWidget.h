#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UImage;
class UButton;
class UTextBlock;

UCLASS()
class PROYECTOINTERMEDIO3_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	void ConfigureMargins();

	void InitializeButton(UButton* Button, UTextBlock* ButtonText, const FString& ButtonTextString);

	UFUNCTION()
	void OnButtonHovered();

	UFUNCTION()
	void OnButtonUnhovered();

	//Fuctions click button
	UFUNCTION()
	void PlayGame();
	UFUNCTION()
	void ExitGame();

private:
	UPROPERTY(meta = (BindWidget))
	class UImage* Background = nullptr;

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

	UTextBlock* CurrentButtonText;
};
