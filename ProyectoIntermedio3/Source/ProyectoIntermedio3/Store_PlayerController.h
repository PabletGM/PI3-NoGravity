
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Store_PlayerController.generated.h"

class UInputMappingContext;
class UMainWidget;


UCLASS()
class PROYECTOINTERMEDIO3_API AStore_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;


	UPROPERTY(EditDefaultsOnly) TSubclassOf<UMainWidget> MainWidgetTemplate = nullptr;

	UPROPERTY()
	UMainWidget* MainWidget = nullptr;
	
};
