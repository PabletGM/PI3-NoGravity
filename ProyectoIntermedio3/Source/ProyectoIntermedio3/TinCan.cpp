#include "TinCan.h"
#include "ProyectoIntermedio3Character.h"
#include <Kismet/GameplayStatics.h>

ATinCan::ATinCan()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATinCan::BuyItem()
{
	Super::BuyItem();

	FPlayerData PlayerData = GameInstance->GetPlayerData();

	PlayerData.MaxWalkSpeed += 50.0f;
}
