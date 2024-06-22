#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};


class PROYECTOINTERMEDIO3_API IInteractable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category = Interact)
	void Interact();

	UFUNCTION(BlueprintNativeEvent, Category = Interact)
	FString GetInteractionText();

	UFUNCTION(BlueprintNativeEvent, Category = Interact)
	FString GetDescriptionText();
};
