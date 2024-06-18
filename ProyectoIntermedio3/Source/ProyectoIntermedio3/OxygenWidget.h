#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OxygenWidget.generated.h"

class UOverlay;
class UImage;

UCLASS()
class PROYECTOINTERMEDIO3_API UOxygenWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UFUNCTION() 
	void OnOxygenChanged(int cur, int max);

private:
	UPROPERTY(meta = (BindWidget))
	UImage* BackgroundBar = nullptr;

	UPROPERTY(meta = (BindWidget))
	UImage* OxygenBar = nullptr;

	FLinearColor GetOxygenColor(float oxygenPercentage) const;
};
