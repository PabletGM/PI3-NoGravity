#include "Store.h"

AStore::AStore()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AStore::BeginPlay()
{
	Super::BeginPlay();
}

void AStore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

