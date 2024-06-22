#include "OxygenWidget.h"
#include "Components/Image.h"
#include "Proyecto3PlayerController.h"
#include "ProyectoIntermedio3Character.h"
#include "OxygenComponent.h"

void UOxygenWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (BackgroundBar)
		BackgroundBar->SetRenderScale({ 1.f, 1.f });
	if (OxygenBar)
		OxygenBar->SetRenderScale({ 1.f, 1.f });
		OxygenBar->SetColorAndOpacity(FLinearColor::Green);

	auto* world = GetWorld();

	if (!world)
		return;

	auto controller = Cast<AProyecto3PlayerController>(world->GetFirstPlayerController());

	if (!controller)
		return;

	auto* player = Cast<AProyectoIntermedio3Character>(controller->GetPawn());

	if (!player || !player->OxygenComponent)
		return;

	player->OxygenComponent->OnOxygenChanged.AddDynamic(this, &UOxygenWidget::OnOxygenChanged);
}

void UOxygenWidget::OnOxygenChanged(int cur, int max)
{
	OxygenBar->SetRenderScale({ (float)cur / (float)max, 1 });

	float percentage = (float)cur / (float)max; //Change color based on remaining oxygen
	FLinearColor color = GetOxygenColor(percentage);
	OxygenBar->SetColorAndOpacity(color);
}

FLinearColor UOxygenWidget::GetOxygenColor(float oxygenPercentage) const
{
	if (oxygenPercentage > 0.5f)
	{
		return FLinearColor::LerpUsingHSV(FLinearColor::Yellow, FLinearColor::Green, (oxygenPercentage - 0.5f) * 2);
	}
	else if (oxygenPercentage > 0.25f)
	{
		return FLinearColor::LerpUsingHSV(FLinearColor::Red, FLinearColor::Yellow, (oxygenPercentage - 0.25f) * 4);
	}
	else
	{
		return FLinearColor::Red;
	}
}