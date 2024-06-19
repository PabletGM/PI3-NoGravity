#include "ShieldWidget.h"
#include "Components/Image.h"
#include "Components/HorizontalBox.h"
#include "Proyecto3PlayerController.h"
#include "ProyectoIntermedio3Character.h"
#include "ShieldComponent.h"

void UShieldWidget::NativeConstruct()
{
	Super::NativeConstruct();

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

void UShieldWidget::UpdateShieldImage(int32 amountShield)
{
    if (ShieldImages.IsValidIndex(amountShield))
    {
        UTexture2D* NewShieldTexture = ShieldImages[amountShield];
        if (NewShieldTexture)
        {
            ShieldImage->SetBrushFromTexture(NewShieldTexture);
        }
    }
}
