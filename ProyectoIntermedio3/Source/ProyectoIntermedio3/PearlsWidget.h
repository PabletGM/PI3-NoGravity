#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PearlsWidget.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class PROYECTOINTERMEDIO3_API UPearlsWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	void ConfigureMargins();

public:
	UFUNCTION()
	void UpdatePearlCount(int32 PearlCount);

private:
	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* HorizontalBox = nullptr;

	UPROPERTY(meta = (BindWidget))
	UImage* PearlImage = nullptr;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CountText = nullptr;
};
