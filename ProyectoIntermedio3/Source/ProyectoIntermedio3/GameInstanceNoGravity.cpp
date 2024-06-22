#include "GameInstanceNoGravity.h"
#include "InventoryComponent.h"
#include "ItemDataAsset.h"
#include "ItemStore.h"

UGameInstanceNoGravity::UGameInstanceNoGravity()
{
	TotalPearls = 0;
}

void UGameInstanceNoGravity::RestoreInventoryIcons(UInventoryComponent* InventoryComponent)
{
    if (!InventoryComponent)
    {
        return;
    }

	if (ItemDataAsset)
	{
		for (int32 i = 0; i < ItemDataAsset->Items.Max(); ++i)
		{
			if (ItemDataAsset->Items[i].amount > 0)
			{
				InventoryComponent->UpdateInventory(ItemDataAsset, i);
			}
		}
	}
}

void UGameInstanceNoGravity::SetTotalPearls(int32 Value)
{
    TotalPearls = Value;
}


