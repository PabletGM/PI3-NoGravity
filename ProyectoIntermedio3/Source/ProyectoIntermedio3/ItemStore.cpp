#include "ItemStore.h"
#include "Store_GameMode.h"

AItemStore::AItemStore()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	SetRootComponent(Mesh);
}

FString AItemStore::GetInteractionText_Implementation()
{
    FString InteractionText = FString::Printf(TEXT("Interact with %s"));

    if (ItemDataAsset && ItemDataAsset->Items.Num() > 0)
    {
        InteractionText += FString::Printf(TEXT(" (%s)"), *ItemDataAsset->Items[0].ItemName);
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

