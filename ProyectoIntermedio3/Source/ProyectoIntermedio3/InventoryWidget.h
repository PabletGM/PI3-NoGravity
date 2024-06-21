#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "InventoryWidget.generated.h"

class UVerticalBox;
class UImage;

UCLASS()
class PROYECTOINTERMEDIO3_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	void ConfigurationWidget();

	UFUNCTION()
	void OnInventoryUpdated(UTexture2D* ItemIcon);

private:
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VerticalBox;

	UPROPERTY(meta = (BindWidget))
	UImage* InventoryImages[6];
};
