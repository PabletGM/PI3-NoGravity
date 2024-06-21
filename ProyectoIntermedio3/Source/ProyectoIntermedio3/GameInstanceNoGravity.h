#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameFramework/Actor.h"
#include "GameInstanceNoGravity.generated.h"

class UInventoryComponent;

UCLASS()
class PROYECTOINTERMEDIO3_API UGameInstanceNoGravity : public UGameInstance
{
	GENERATED_BODY()

public:
	UGameInstanceNoGravity();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<UTexture2D*> ItemsPurchasedIcons;

	void SaveInventoryIcons(UInventoryComponent* InventoryComponent);
	void RestoreInventoryIcons(UInventoryComponent* InventoryComponent);

	UFUNCTION()
	void SetTotalPearls(int32 Value);

	UFUNCTION()
	int32 GetTotalPearls() const { return TotalPearls; }

protected:
	UPROPERTY()
	int32 TotalPearls;
};
