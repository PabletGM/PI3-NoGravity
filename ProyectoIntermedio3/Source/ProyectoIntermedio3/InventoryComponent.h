#pragma once

#include "CoreMinimal.h"
#include "ItemDataAsset.h"
#include "Components/ActorComponent.h"

#include "InventoryComponent.generated.h"


class UInventoryComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventoryUpdated, UTexture2D*, ItemIcon);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROYECTOINTERMEDIO3_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

	void UpdateInventory(UItemDataAsset* dataAsset, int32 index);

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryUpdated OnInventoryUpdated;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	int32 Capacity;
};
