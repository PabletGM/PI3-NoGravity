#include "GameInstanceNoGravity.h"
#include "InventoryComponent.h"
#include "ItemStore.h"

UGameInstanceNoGravity::UGameInstanceNoGravity()
{
	TotalPearls = 0;
}

void UGameInstanceNoGravity::SaveInventoryIcons(UInventoryComponent* InventoryComponent)
{
    if (!InventoryComponent)
    {
        return;
    }

    ItemsPurchasedStore.Empty(); 

    for (int32 i = 0; i < InventoryComponent->GetNumItemsPurchased(); ++i)
    {
        AItemStore* Item = InventoryComponent->GetItem(i);
        if (Item)
        {
            ItemsPurchasedStore.Add(Item);
        }
        else
        {
            ItemsPurchasedStore.Add(nullptr);
        }
    }

    UE_LOG(LogTemp, Log, TEXT("SaveInventoryIcons: Saved %d items' to ItemsPurchasedIcons."), ItemsPurchasedStore.Num());
}

void UGameInstanceNoGravity::RestoreInventoryIcons(UInventoryComponent* InventoryComponent)
{
    if (!InventoryComponent)
    {
        return;
    }

    for (int32 i = 0; i < ItemsPurchasedStore.Num(); ++i)
    {
        AItemStore* Item = ItemsPurchasedStore[i];
        if (Item)
        {
            InventoryComponent->AddItem(Item);
            InventoryComponent->OnInventoryUpdated.Broadcast(Item->GetItemIcon());
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("RestoreInventoryIcons: Null item found in ItemsPurchasedStore."));
        }
    }

    UE_LOG(LogTemp, Log, TEXT("RestoreInventoryIcons: Restored %d items from ItemsPurchasedStore."), ItemsPurchasedStore.Num());
}

void UGameInstanceNoGravity::SetTotalPearls(int32 Value)
{
    TotalPearls = Value;
}

