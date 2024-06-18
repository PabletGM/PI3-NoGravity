#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

UCLASS()
class PROYECTOINTERMEDIO3_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(Category = "UI")
	void ShowConcreteWidget(UUserWidget* WidgetToShow);

	UFUNCTION(Category = "UI")
	void ShowAllWidgets();

	//Widgets
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) 
	UUserWidget* PearlsWidget = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UUserWidget* OxygenWidget = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UUserWidget* InteractWidget = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UUserWidget* GameOverWidget = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UUserWidget* DamageWidget = nullptr;
};
