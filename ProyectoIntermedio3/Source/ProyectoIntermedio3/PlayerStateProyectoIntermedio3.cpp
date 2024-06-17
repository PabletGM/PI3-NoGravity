#include "PlayerStateProyectoIntermedio3.h"
#include "PearlsWidget.h"
#include "GameInstanceNoGravity.h"

void APlayerStateProyectoIntermedio3::AddPearl(int32 value)
{
	totalPealrs += value;

	OnPearlCountChanged.Broadcast(totalPealrs);

	GameInstance->SetTotalPearls(value); //CORRECT: PASS INFORMATION PEARLS WHEN CHANGE SCENE TO STORE ONLY
}