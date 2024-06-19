#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "ShieldWidget.generated.h"

class UHorizontalBox;
class UOverlay;
class UImage;

UCLASS()
class PROYECTOINTERMEDIO3_API UShieldWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void UpdateShieldImage(int AmountShield);

private:
	UPROPERTY(meta = (BindWidget))
	UOverlay* Overlay = nullptr;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* HorizontalBox = nullptr;

	UPROPERTY(meta = (BindWidget))
	UImage* ShieldImage = nullptr;

	UPROPERTY()
	TArray<UTexture2D*> ShieldImages;
};
