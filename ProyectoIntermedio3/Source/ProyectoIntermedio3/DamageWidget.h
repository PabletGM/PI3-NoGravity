#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DamageWidget.generated.h"

class UImage;

UCLASS()
class PROYECTOINTERMEDIO3_API UDamageWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void ShowDamageEffect();

	UFUNCTION()
	void HideDamageEffect();

	void UpdateFadeEffect();


protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly)
	float FadeDuration = 1.5f; 

	float FadeTimer = 0.0f; 

private:
	UPROPERTY(meta = (BindWidget))
	UImage* DamageImage = nullptr;

	FTimerHandle DamageTimer;
};
