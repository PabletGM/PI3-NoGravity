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
}

void UMainWidget::ShowAllWidgets()
{
    PearlsWidget->SetVisibility(ESlateVisibility::Visible);
    OxygenWidget->SetVisibility(ESlateVisibility::Visible);
}
