#include "GameInstanceNoGravity.h"
#include "AudioManager.h"
#include "InventoryComponent.h"
#include "ItemStore.h"
#include "Kismet/GameplayStatics.h"

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

    ItemsPurchasedIcons.Empty();

    for (int32 i = 0; i < InventoryComponent->GetNumItemsPurchased(); ++i)
    {
        AItemStore* Item = InventoryComponent->GetItem(i);

        if (Item)
        {
            UTexture2D* ItemIcon = Item->GetItemIcon();

            if (ItemIcon)
            {
                ItemsPurchasedIcons.Add(ItemIcon);
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("SaveInventoryIcons: Found NULL Item at index %d"), i);
        }
    }

    UE_LOG(LogTemp, Log, TEXT("SaveInventoryIcons: Saved %d items' icons to ItemsPurchasedIcons."), ItemsPurchasedIcons.Num());
}

void UGameInstanceNoGravity::RestoreInventoryIcons(UInventoryComponent* InventoryComponent)
{
    if (!InventoryComponent)
    {
        return;
    }

  
}

void UGameInstanceNoGravity::SetTotalPearls(int32 Value)
{
    TotalPearls = Value;
}

