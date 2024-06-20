#include "TinCan.h"
#include "ProyectoIntermedio3Character.h"
#include "GameInstanceNoGravity.h"
#include <Kismet/GameplayStatics.h>

ATinCan::ATinCan()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATinCan::BuyItem()
{
	Super::BuyItem();

}
