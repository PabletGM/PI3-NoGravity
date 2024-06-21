#include "Store_PlayerController.h"
#include <EnhancedInputSubsystems.h>
#include "MainWidget.h"
#include <Kismet/GameplayStatics.h>
#include "Camera/CameraActor.h"

void AStore_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);

		UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
	}

    if (MainWidgetTemplate)
    {
        MainWidget = CreateWidget<UMainWidget>(this, MainWidgetTemplate);
        if (MainWidget)
        {
            MainWidget->ShowConcreteWidget(MainWidget->PearlsWidget);
            MainWidget->AddToViewport(0);
            bShowMouseCursor = false;
        }
    }

    ACameraActor* CameraActor = Cast<ACameraActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ACameraActor::StaticClass()));
    if (CameraActor)
    {
        SetViewTarget(CameraActor);
    }
}
