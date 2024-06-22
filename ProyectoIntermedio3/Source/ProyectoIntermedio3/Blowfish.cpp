#include "Blowfish.h"
#include "GameInstanceNoGravity.h"
#include "ProyectoIntermedio3Character.h"
#include <Kismet/GameplayStatics.h>

ABlowfish::ABlowfish()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABlowfish::BuyItem()
{
	Super::BuyItem();
	GameInstance->PlayerDataAsset->PlayerData.CurrentShield = 3;
}
