#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "ShieldWidget.generated.h"

class UHorizontalBox;
class UImage;

UCLASS()
class PROYECTOINTERMEDIO3_API UShieldWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void UpdateShieldImage(int32 AmountShield);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shield")
	TArray<UTexture2D*> ShieldImages;

private:
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* HorizontalBox = nullptr;

	UPROPERTY(meta = (BindWidget))
	UImage* ShieldImage = nullptr;
};
