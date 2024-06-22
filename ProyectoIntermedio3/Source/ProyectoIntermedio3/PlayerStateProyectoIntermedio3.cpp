#include "PlayerStateProyectoIntermedio3.h"
#include "PearlsWidget.h"
#include "GameInstanceNoGravity.h"
#include <Kismet/GameplayStatics.h>

APlayerStateProyectoIntermedio3::APlayerStateProyectoIntermedio3()
{
    GameInstance = Cast<UGameInstanceNoGravity>(UGameplayStatics::GetGameInstance(GetWorld()));
}

void APlayerStateProyectoIntermedio3::BeginPlay()
{
    Super::BeginPlay();

    UpdateWidgetPearl();
}

void APlayerStateProyectoIntermedio3::AddPearl(int32 value)
{
	totalPearls += value;

	GameInstance->SetTotalPearls(totalPearls);

    UpdateWidgetPearl();
}

void APlayerStateProyectoIntermedio3::UpdateWidgetPearl()
{
    totalPearls = GameInstance->GetTotalPearls();
    OnPearlCountChanged.Broadcast(totalPearls);
}
