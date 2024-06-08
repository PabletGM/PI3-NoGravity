#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>

void UMainMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (GameTitleText)
    {
        GameTitleText->SetText(FText::FromString(TEXT("PI3")));
    }

    InitializeButtons();

    ConfigureMargins();
}

void UMainMenuWidget::InitializeButtons()
{
    if (PlayButton)
    {
        PlayButton->OnClicked.AddDynamic(this, &UMainMenuWidget::PlayGame);
    }

    if (PlayButtonText)
    {
        PlayButtonText->SetText(FText::FromString(TEXT("Play")));
    }

    if (QuitButton)
    {
        QuitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::ExitGame);
    }

    if (QuitButtonText)
    {
        QuitButtonText->SetText(FText::FromString(TEXT("Quit")));
    }
}

void UMainMenuWidget::PlayGame()
{
    UGameplayStatics::OpenLevel(this, FName("Game"));
}

void UMainMenuWidget::ExitGame()
{
    UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}

void UMainMenuWidget::ConfigureMargins()
{
    if (ButtonContainer)
    {
        UVerticalBoxSlot* PlayButtonSlot = Cast<UVerticalBoxSlot>(PlayButton->Slot);

        if (PlayButtonSlot)
        {
            PlayButtonSlot->SetPadding(FMargin(0, 0, 0, 20));
        }

        UVerticalBoxSlot* QuitButtonSlot = Cast<UVerticalBoxSlot>(QuitButton->Slot);

        if (QuitButtonSlot)
        {
            QuitButtonSlot->SetPadding(FMargin(0, 20, 0, 0));
        }
    }
}