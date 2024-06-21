#include "ItemStore.h"
#include "Store_GameMode.h"
#include "ProyectoIntermedio3Character.h"
#include "InventoryComponent.h"

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
    AProyectoIntermedio3Character* PlayerCharacter = Cast<AProyectoIntermedio3Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    if (PlayerCharacter)
    {
        UInventoryComponent* InventoryComponent = PlayerCharacter->InventoryComponent;

        if (InventoryComponent)
        {
            InventoryComponent->AddItem(this);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("InventoryComponent not found on player character!"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Player character not found!"));
    }

    Destroy();
}

