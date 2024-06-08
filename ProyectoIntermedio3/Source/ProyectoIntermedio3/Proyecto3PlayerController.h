#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Proyecto3PlayerController.generated.h"

class UInputMappingContext;
class UMainWidget;

UCLASS()
class PROYECTOINTERMEDIO3_API AProyecto3PlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

public:
	UPROPERTY(EditDefaultsOnly) TSubclassOf<UMainWidget> MainWidgetTemplate = nullptr;

	UPROPERTY()
	UMainWidget* MainWidget = nullptr;
};
