#include "DiveGlasses.h"
#include "GameInstanceNoGravity.h"
#include "ProyectoIntermedio3Character.h"
#include <Kismet/GameplayStatics.h>

ADiveGlasses::ADiveGlasses()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADiveGlasses::BuyItem()
{
	Super::BuyItem();
	GameInstance->PlayerDataAsset->PlayerData.OxygenDecrement += 0.5f;
}


