#include "TinCan.h"
#include "ProyectoIntermedio3Character.h"
#include <Kismet/GameplayStatics.h>

#include "GameInstanceNoGravity.h"

ATinCan::ATinCan()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATinCan::BuyItem()
{
    Super::BuyItem();
    GameInstance->PlayerDataAsset->PlayerData.MaxWalkSpeed += 50.f;
}
