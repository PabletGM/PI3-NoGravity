#include "PlayerStateProyectoIntermedio3.h"
#include "PearlsWidget.h"

void APlayerStateProyectoIntermedio3::AddPearl(int32 value)
{
	totalPealrs += value;

	OnPearlCountChanged.Broadcast(totalPealrs);
}