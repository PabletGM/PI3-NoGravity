#include "InventoryWidget.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	auto* world = GetWorld();

	if (!world)
		return;

	auto controller = Cast<AProyecto3PlayerController>(world->GetFirstPlayerController());

	if (!controller)
		return;

	auto* player = Cast<AProyectoIntermedio3Character>(controller->GetPawn());

	if (!player || !player->InventoryComponent)
		return;

	player->InventoryComponent->OnInventoryUpdated.AddDynamic(this, &UInventoryWidget::OnInventoryUpdated);
}

void UInventoryWidget::OnInventoryUpdated()
{
	
}