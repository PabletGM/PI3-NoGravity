#include "InventoryWidget.h"
#include "Components/Image.h"
#include "Components/VerticalBox.h"
#include "Store_PlayerController.h"
#include "CharacterStore.h"
#include "Components/VerticalBoxSlot.h"
#include <Kismet/GameplayStatics.h>
#include "ProyectoIntermedio3Character.h"
#include "Proyecto3PlayerController.h"
#include "Store_PlayerController.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

    ConfigurationWidget();

    FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld(), true);

	auto* world = GetWorld();

	if (!world)
		return;

    if (CurrentLevelName.Equals("L_Store", ESearchCase::IgnoreCase))
    {
        auto controller = Cast<AStore_PlayerController>(world->GetFirstPlayerController());
        auto* player = Cast<ACharacterStore>(controller->GetPawn()); 

        if (!controller || !player->InventoryComponent)
            return;

        player->InventoryComponent->OnInventoryUpdated.AddDynamic(this, &UInventoryWidget::OnInventoryUpdated);
    }
    else if (CurrentLevelName.Equals("L_MainLevel", ESearchCase::IgnoreCase))
    {
        auto controller = Cast<AProyecto3PlayerController>(world->GetFirstPlayerController());
        auto* player = Cast<AProyectoIntermedio3Character>(controller->GetPawn());

        if(!controller || !player->InventoryComponent)
            return;

        player->InventoryComponent->OnInventoryUpdated.AddDynamic(this, &UInventoryWidget::OnInventoryUpdated);
    }
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
                InventoryImages[i]->Brush.ImageSize.X = 25.0f;
                InventoryImages[i]->Brush.ImageSize.Y = 125.0f;
                NewSlot->SetPadding(FMargin(0.f, 10.f, 0.f, 0.f)); 
            }
        }
    }
}

void UInventoryWidget::OnInventoryUpdated(UTexture2D* ItemIcon)
{
    if (!ItemIcon)
		return;


    for (int32 i = 0; i < 6; ++i)
    {
        if (InventoryImages[i] && InventoryImages[i]->Brush.GetResourceObject() == nullptr)
        {
            InventoryImages[i]->SetBrushFromTexture(ItemIcon);
            break;
        }
    }
}
