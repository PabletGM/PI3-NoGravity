#include "InteractWidget.h"
#include "Components/TextBlock.h"
#include "CharacterStore.h"

void UInteractWidget::NativeConstruct()
{
    Super::NativeConstruct();

    TextInteract->SetVisibility(ESlateVisibility::Collapsed);

    if (ACharacterStore* PlayerCharacter = Cast<ACharacterStore>(GetOwningPlayerPawn()))
    {
        PlayerCharacter->OnInteract.BindDynamic(this, &UInteractWidget::SetInteractText);

        TextInteract->SetVisibility(ESlateVisibility::Visible);
    }
}

void UInteractWidget::SetInteractText(FString Text)
{
    TextInteract->SetText(FText::FromString(Text));
}
