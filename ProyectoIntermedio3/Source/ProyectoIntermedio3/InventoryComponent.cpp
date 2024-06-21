#include "InventoryComponent.h"
#include "ItemStore.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	Capacity = 6;
}

AItemStore* UInventoryComponent::GetItem(int32 Index) const
{
	if (Index >= 0 && Index < ItemsPurchased.Num())
	{
		return ItemsPurchased[Index];
	}

	return nullptr;
}

bool UInventoryComponent::AddItem(AItemStore* Item)
{
	if(ItemsPurchased.Num() >= Capacity || !Item)
	{
		return false;
	}

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("ADDD"));
	ItemsPurchased.Add(Item);
	OnInventoryUpdated.Broadcast(Item->GetItemIcon());

	return true;
}

bool UInventoryComponent::RemoveItem(AItemStore* Item)
{
	if (Item)
	{
		ItemsPurchased.RemoveSingle(Item);

		OnInventoryUpdated.Broadcast(nullptr);

		return true;
	}

	return false;
}