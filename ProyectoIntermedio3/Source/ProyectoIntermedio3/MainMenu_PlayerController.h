#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainMenu_PlayerController.generated.h"

class UInputMappingContext;
class UMainMenuWidget;

UCLASS()
class PROYECTOINTERMEDIO3_API AMainMenu_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMainMenuWidget> MainMenuWidgetTemplate = nullptr;

	UPROPERTY()
	UMainMenuWidget* MainMenuWidget = nullptr;
};
