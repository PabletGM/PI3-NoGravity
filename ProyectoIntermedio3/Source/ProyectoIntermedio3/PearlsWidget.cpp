#include "PearlsWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "PlayerStateProyectoIntermedio3.h"

void UPearlsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ConfigureMargins();

	UpdatePearlCount(0);

    APlayerStateProyectoIntermedio3* PlayerState = Cast<APlayerStateProyectoIntermedio3>(GetOwningPlayerState());

    if (PlayerState)
    {
        PlayerState->OnPearlCountChanged.AddDynamic(this, &UPearlsWidget::UpdatePearlCount);
    }
}

void UPearlsWidget::UpdatePearlCount(int32 PearlCount)
{
    if (CountText)
    {
        CountText->SetText(FText::FromString(FString::Printf(TEXT("x %d"), PearlCount)));
    }
}

void UPearlsWidget::ConfigureMargins()
{
    if (HorizontalBox)
    {
        HorizontalBox->ClearChildren();

        UHorizontalBoxSlot* ImageSlot = HorizontalBox->AddChildToHorizontalBox(PearlImage);
        if (ImageSlot)
        {
            ImageSlot->SetPadding(FMargin(0, 0, 10, 0));
            ImageSlot->SetSize(FSlateChildSize(ESlateSizeRule::Automatic));

            PearlImage->SetBrushSize(FVector2D(62.0f, 62.f)); 
        }

        UHorizontalBoxSlot* TextSlot = HorizontalBox->AddChildToHorizontalBox(CountText);
        if (TextSlot)
        {
            TextSlot->SetPadding(FMargin(10, 0, 0, 0));
            TextSlot->SetSize(FSlateChildSize(ESlateSizeRule::Automatic));
            TextSlot->SetVerticalAlignment(VAlign_Center);
        }
    }
}