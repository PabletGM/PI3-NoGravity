#pragma once

#include "CoreMinimal.h"
#include "ItemDataAsset.h"
#include "Components/ActorComponent.h"

#include "InventoryComponent.generated.h"

class AItemStore;
class UInventoryComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventoryUpdated, UTexture2D*, ItemIcon);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROYECTOINTERMEDIO3_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

	bool AddItem(AItemStore* Item);
	bool RemoveItem(AItemStore* Item);

	void UpdateInventory(UItemDataAsset* dataAsset, int32 index);

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryUpdated OnInventoryUpdated;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	int32 Capacity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
	TArray<AItemStore*> ItemsPurchased;

	AItemStore* GetItem(int32 Index) const;

	int32 GetNumItemsPurchased() const { return ItemsPurchased.Num(); }

};
