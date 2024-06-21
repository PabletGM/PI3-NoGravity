#include "ItemStore.h"
#include "Store_GameMode.h"
#include "CharacterStore.h"
#include "Kismet/GameplayStatics.h"
#include "InventoryComponent.h"
#include "Engine/Engine.h"

AItemStore::AItemStore()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	SetRootComponent(Mesh);
}

void AItemStore::InitializeItem()
{
    if (!ItemDataAsset || ItemIndex >= ItemDataAsset->Items.Num())
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid Item Data Asset or Item Index"));
        return;
    }

    const FItemInfoStruct& ItemInfo = ItemDataAsset->Items[ItemIndex];
}

int32 AItemStore::GetItemPrice() const
{
    if (ItemDataAsset && ItemIndex < ItemDataAsset->Items.Num())
    {
        return ItemDataAsset->Items[ItemIndex].ItemPrice;
    }

    return 0;
}

UTexture2D* AItemStore::GetItemIcon() const
{
    if (ItemDataAsset && ItemIndex < ItemDataAsset->Items.Num())
    {
        return ItemDataAsset->Items[ItemIndex].ItemIcon; 
    }

    return nullptr;
}

FString AItemStore::GetInteractionText_Implementation()
{
    FString InteractionText = "Buy ";

    if (ItemDataAsset && ItemIndex < ItemDataAsset->Items.Num())
    {
        InteractionText += ItemDataAsset->Items[ItemIndex].ItemName;
    }

    return InteractionText;
}

void AItemStore::Interact_Implementation()
{
    AStore_GameMode* GameMode = Cast<AStore_GameMode>(GetWorld()->GetAuthGameMode());

    if (GameMode)
    {
        GameMode->BuyItem(this);
    }
}

void AItemStore::BuyItem()
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    ACharacterStore* PlayerCharacter = Cast<ACharacterStore>(UGameplayStatics::GetPlayerCharacter(World, 0));
    if (!PlayerCharacter)
    {
        return;
    }

    UInventoryComponent* InventoryComponent = PlayerCharacter->InventoryComponent;
    if (!InventoryComponent)
    {
        return;
    }

    InventoryComponent->AddItem(this);

    InventoryComponent->UpdateInventory(ItemDataAsset, ItemIndex);

    Destroy();
}

