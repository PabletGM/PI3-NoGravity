#include "MainMenuWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>

#include "MainMenu_GameModeBase.h"
#include "Fonts/SlateFontInfo.h"

void UMainMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (GameTitleText)
    {
        GameTitleText->SetText(FText::FromString(TEXT("Zero - G")));
        FSlateFontInfo FontInfo = GameTitleText->Font;
        FontInfo.Size = 120;
        GameTitleText->SetFont(FontInfo);
    }

    InitializeButton(PlayButton, PlayButtonText, TEXT("Play"));
    InitializeButton(QuitButton, QuitButtonText, TEXT("Quit"));

    ConfigureMargins();
}

void UMainMenuWidget::InitializeButton(UButton* Button, UTextBlock* ButtonText, const FString& ButtonTextString)
{
    if (Button && ButtonText)
    {
        ButtonText->SetText(FText::FromString(ButtonTextString));

        Button->OnHovered.AddDynamic(this, &UMainMenuWidget::OnButtonHovered);
        Button->OnUnhovered.AddDynamic(this, &UMainMenuWidget::OnButtonUnhovered);

        if (Button == PlayButton)
        {
            Button->OnClicked.AddDynamic(this, &UMainMenuWidget::PlayGame);
        }
        else if (Button == QuitButton)
        {
            Button->OnClicked.AddDynamic(this, &UMainMenuWidget::ExitGame);
        }
    }
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

void UMainMenuWidget::PlayGame()
{
    //call MainMenu_GameMode and method sound
    AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this);
    if(GameMode)
    {
        AMainMenu_GameModeBase* MainMenu_GameMode = Cast<AMainMenu_GameModeBase>(GameMode);
        if(MainMenu_GameMode)
        {
            MainMenu_GameMode->MakeSoundEffect1("Selection_Changes");
        }
    }
    
    UGameplayStatics::OpenLevel(this, FName("L_Store"));
}

void UMainMenuWidget::ExitGame()
{
    //call MainMenu_GameMode and method sound
    AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this);
    if(GameMode)
    {
        AMainMenu_GameModeBase* MainMenu_GameMode = Cast<AMainMenu_GameModeBase>(GameMode);
        if(MainMenu_GameMode)
        {
            MainMenu_GameMode->MakeSoundEffect1("Selection_Changes");
        }
    }
    UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}

void UMainMenuWidget::OnButtonHovered()
{
    if (PlayButton->IsHovered())
    {
        PlayButtonText->SetColorAndOpacity(FLinearColor(0.715693f, 0.964686f, 0.0f, 1.0f));
    }
    else if (QuitButton->IsHovered())
    {
        QuitButtonText->SetColorAndOpacity(FLinearColor(0.715693f, 0.964686f, 0.0f, 1.0f));
    }
}

void UMainMenuWidget::OnButtonUnhovered()
{
    PlayButtonText->SetColorAndOpacity(FLinearColor::White);
    QuitButtonText->SetColorAndOpacity(FLinearColor::White);
}