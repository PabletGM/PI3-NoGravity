#include "ItemStore.h"
#include "Store_GameMode.h"
#include "CharacterStore.h"
#include "Kismet/GameplayStatics.h"
#include "InventoryComponent.h"
#include "Engine/Engine.h"
#include "Components/TextRenderComponent.h"
#include "GameInstanceNoGravity.h"

AItemStore::AItemStore()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	SetRootComponent(Mesh);

    TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ItemPriceText"));
    TextRenderComponent->SetupAttachment(RootComponent); 
    TextRenderComponent->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
    TextRenderComponent->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
    TextRenderComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 250.0f));
    TextRenderComponent->SetWorldSize(85.0f);
}

void AItemStore::BeginPlay()
{
    Super::BeginPlay();

    FString PriceText = FString::Printf(TEXT("%d$"), GetItemPrice());
    TextRenderComponent->SetText(FText::FromString(PriceText));

    GameInstance = Cast<UGameInstanceNoGravity>(GetGameInstance());
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

FString AItemStore::GetDescriptionText_Implementation()
{
    FString DescriptionText;

    if (ItemDataAsset && ItemIndex < ItemDataAsset->Items.Num())
    {
        DescriptionText += ItemDataAsset->Items[ItemIndex].Description;
    }

    return DescriptionText;
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

    InventoryComponent->UpdateInventory(ItemDataAsset, ItemIndex);

    Destroy();
}