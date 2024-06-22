#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameFramework/Actor.h"
#include "ItemStore.h"
#include "GameInstanceNoGravity.generated.h"

class UInventoryComponent;
class UItemDataAsset;

UCLASS()
class PROYECTOINTERMEDIO3_API UGameInstanceNoGravity : public UGameInstance
{
	GENERATED_BODY()

public:
	UGameInstanceNoGravity();

	void RestoreInventoryIcons(UInventoryComponent* InventoryComponent);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Items")
	UItemDataAsset* ItemDataAsset;

	UFUNCTION()
	void SetTotalPearls(int32 Value);

	UFUNCTION()
	int32 GetTotalPearls() const { return TotalPearls; }

protected:
	UPROPERTY()
	int32 TotalPearls;
};
