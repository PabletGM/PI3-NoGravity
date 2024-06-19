#include "GameInstanceNoGravity.h"
#include "GameInstanceNoGravity.h"

#include "AudioManager.h"
#include "Kismet/GameplayStatics.h"

UGameInstanceNoGravity::UGameInstanceNoGravity()
{
	TotalPearls = 0;
}


void UGameInstanceNoGravity::SetTotalPearls(int32 Value)
{
	TotalPearls = Value;
}


void UGameInstanceNoGravity::Init()
{
	Super::Init();

}




