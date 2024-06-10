#include "InteractWidget.h"
#include "Components/TextBlock.h"
#include "ProyectoIntermedio3Character.h"

void UInteractWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (AProyectoIntermedio3Character* PlayerCharacter = Cast<AProyectoIntermedio3Character>(GetOwningPlayerPawn()))
    {
        PlayerCharacter->OnInteract.BindDynamic(this, &UInteractWidget::SetInteractText);
    }
}

void UInteractWidget::SetInteractText(FString Text)
{
    TextInteract->SetText(FText::FromString(Text));
}
