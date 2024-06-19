#include "ShieldWidget.h"
#include "Components/Image.h"
#include "Components/Overlay.h"
#include "Components/HorizontalBox.h"
#include "Proyecto3PlayerController.h"
#include "ProyectoIntermedio3Character.h"
#include "ShieldComponent.h"

void UShieldWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Overlay->AddChildToOverlay(HorizontalBox);

	HorizontalBox->AddChildToHorizontalBox(ShieldImage);

	auto* world = GetWorld();

	if (!world)
		return;

	auto controller = Cast<AProyecto3PlayerController>(world->GetFirstPlayerController());

	if (!controller)
		return;

	auto* player = Cast<AProyectoIntermedio3Character>(controller->GetPawn());

	if (!player || !player->ShieldComponent)
		return;

	player->ShieldComponent->OnShieldChanged.AddDynamic(this, &UShieldWidget::UpdateShieldImage);
}

void UShieldWidget::UpdateShieldImage(int AmountShield)
{
    if (ShieldImages.IsValidIndex(AmountShield))
    {
        UTexture2D* NewShieldTexture = ShieldImages[AmountShield];
        if (NewShieldTexture)
        {
            ShieldImage->SetBrushFromTexture(NewShieldTexture);
        }
    }
}
