#include "TinCan.h"
#include "ProyectoIntermedio3Character.h"
#include <Kismet/GameplayStatics.h>

ATinCan::ATinCan()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATinCan::BuyItem()
{
    if (GameInstance && GameInstance->PlayerDataAsset)
    {
        Super::BuyItem();

        GameInstance->PlayerDataAsset->PlayerData.MaxWalkSpeed *= 50.f;
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("GameInstance o PlayerDataAsset no está definido en ATinCan."));
    }
}
