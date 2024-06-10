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

void UOxygenWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UOxygenWidget::OnOxygenChanged(int cur, int max)
{
	OxygenBar->SetRenderScale({ (float)cur / (float)max, 1 });
}
