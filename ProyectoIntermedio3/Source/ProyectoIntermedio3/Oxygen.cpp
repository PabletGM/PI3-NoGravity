#include "Oxygen.h"

#include "OxygenComponent.h"
#include "ProyectoIntermedio3Character.h"

AOxygen::AOxygen()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AOxygen::Collected(AActor* Collector)
{
    AProyectoIntermedio3Character* Character = Cast<AProyectoIntermedio3Character>(Collector);

    if (Character && Character->OxygenComponent)
    {
        Character->OxygenComponent->AddOxygen(20);
    }
}
