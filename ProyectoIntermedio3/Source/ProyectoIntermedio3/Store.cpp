#include "Store.h"
#include "ItemStore.h"
#include "PlayerStateProyectoIntermedio3.h"
#include "GameInstanceNoGravity.h"

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