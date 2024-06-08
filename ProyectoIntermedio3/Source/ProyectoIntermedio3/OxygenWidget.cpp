#include "OxygenWidget.h"
#include "Components/Image.h"

void UOxygenWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (BackgroundBar)
		BackgroundBar->SetRenderScale({ 1.f, 1.f });
	if (OxygenBar)
		OxygenBar->SetRenderScale({ 1.f, 1.f });
}

void UOxygenWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UOxygenWidget::OnOxygenChanged(int cur, int max)
{
	OxygenBar->SetRenderScale({ (float)cur / (float)max, 1 });
}
