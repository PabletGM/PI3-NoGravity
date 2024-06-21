#include "InventoryComponent.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	Capacity = 6;
}

bool UInventoryComponent::AddItem(AItemStore* Item)
{
	if(ItemsPurchased.Num() >= Capacity || !Item)
	{
		return false;
	}

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


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

