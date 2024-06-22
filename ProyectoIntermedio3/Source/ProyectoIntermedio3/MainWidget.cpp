#include "MainWidget.h"

void UMainWidget::ShowConcreteWidget(UUserWidget* WidgetToShow)
{
    if (PearlsWidget)
    {
        PearlsWidget->SetVisibility(WidgetToShow == PearlsWidget ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
    }

    if (OxygenWidget)
    {
        OxygenWidget->SetVisibility(WidgetToShow == OxygenWidget ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
    }

    if (ShieldWidget)
    {
        ShieldWidget->SetVisibility(WidgetToShow == ShieldWidget ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
    }

    if (InventoryWidget)
    {
        InventoryWidget->SetVisibility(WidgetToShow == InventoryWidget ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
    }

    if (GameOverWidget)
    {
        GameOverWidget->SetVisibility(WidgetToShow == GameOverWidget ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
    }
}

void UMainWidget::ShowAllWidgets()
{
    PearlsWidget->SetVisibility(ESlateVisibility::Visible);
    OxygenWidget->SetVisibility(ESlateVisibility::Visible);
    ShieldWidget->SetVisibility(ESlateVisibility::Visible);
    InventoryWidget->SetVisibility(ESlateVisibility::Visible);
}
