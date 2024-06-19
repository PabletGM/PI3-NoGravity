#include "Shield.h"
#include "ProyectoIntermedio3Character.h"

AShield::AShield()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AShield::Collected(AActor* Collector)
{
    AProyectoIntermedio3Character* Character = Cast<AProyectoIntermedio3Character>(Collector);
    if (Character && Character->ShieldComponent)
    {
        Character->ShieldComponent->AddShield(1); 
    }
}

