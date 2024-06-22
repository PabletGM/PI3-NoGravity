#include "InteractWidget.h"
#include "Components/TextBlock.h"
#include "CharacterStore.h"

void UInteractWidget::NativeConstruct()
{
    Super::NativeConstruct();

    TextInteract->SetVisibility(ESlateVisibility::Collapsed);
    TextDescription->SetVisibility(ESlateVisibility::Collapsed);

    if (ACharacterStore* PlayerCharacter = Cast<ACharacterStore>(GetOwningPlayerPawn()))
    {
        PlayerCharacter->OnInteract.BindDynamic(this, &UInteractWidget::SetInteractText);

        TextInteract->SetVisibility(ESlateVisibility::Visible);
        TextDescription->SetVisibility(ESlateVisibility::Visible);
    }
}

void UInteractWidget::SetInteractText(FString Text,  FString ItemDescription)
{
    TextInteract->SetText(FText::FromString(Text));
    TextDescription->SetText(FText::FromString(ItemDescription));

    TextInteract->SetVisibility(ESlateVisibility::Visible);
    TextDescription->SetVisibility(ESlateVisibility::Visible);
}
