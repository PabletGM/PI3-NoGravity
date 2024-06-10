#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

UCLASS()
class PROYECTOINTERMEDIO3_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) 
	UUserWidget* PearlsWidget = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UUserWidget* OxygenWidget = nullptr;
};