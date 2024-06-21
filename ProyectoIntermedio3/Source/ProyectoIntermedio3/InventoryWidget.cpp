#include "InventoryWidget.h"
#include "Components/Image.h"
#include "Components/VerticalBox.h"
#include "Store_PlayerController.h"
#include "CharacterStore.h"
#include "ItemStore.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

    ConfigurationWidget();

	auto* world = GetWorld();

	if (!world)
		return;

	auto controller = Cast<AStore_PlayerController>(world->GetFirstPlayerController());

	if (!controller)
		return;

	auto* player = Cast<ACharacterStore>(controller->GetPawn());

	if (!player || !player->InventoryComponent)
		return;

	player->InventoryComponent->OnInventoryUpdated.AddDynamic(this, &UInventoryWidget::OnInventoryUpdated);
}

void UInventoryWidget::ConfigurationWidget()
{
    if (VerticalBox)
    {
        VerticalBox->ClearChildren();
        
        for (int32 i = 0; i < 6; ++i)
        {
            UVerticalBoxSlot* NewSlot = Cast<UVerticalBoxSlot>(VerticalBox->AddChild(InventoryImages[i]));

            if (NewSlot)
            {
                InventoryImages[i]->Brush.ImageSize.X = 32.0f;
                InventoryImages[i]->Brush.ImageSize.Y = 125.0f;
                NewSlot->SetPadding(FMargin(0.f, 10.f, 0.f, 0.f)); 
            }
        }

    }
}

void UInventoryWidget::OnInventoryUpdated(UTexture2D* ItemIcon)
{
    if (!ItemIcon)
    {
        return;
    }

    GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::Printf(TEXT("ItemIcon: %s"), *ItemIcon->GetName()));

    for (int32 i = 0; i < 6; ++i)
    {
        if (InventoryImages[i] && InventoryImages[i]->Brush.GetResourceObject() == nullptr)
        {
            InventoryImages[i]->SetBrushFromTexture(ItemIcon);
            break;
        }
    }
}