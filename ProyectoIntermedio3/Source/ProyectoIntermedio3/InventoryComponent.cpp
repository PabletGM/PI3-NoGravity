#include "InventoryComponent.h"
#include "ItemStore.h"
#include "GameInstanceNoGravity.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	Capacity = 6;
}

void UInventoryComponent::UpdateInventory(UItemDataAsset* dataAsset, int32 index)
{
	if (!dataAsset || index < 0 || index >= Capacity)
	{
		return;
	}

	dataAsset->Items[index].amount += 1;

	OnInventoryUpdated.Broadcast(dataAsset->Items[index].ItemIcon);
}


