#include "StoreItemSpawner.h"

AStoreItemSpawner::AStoreItemSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AStoreItemSpawner::BeginPlay()
{
	Super::BeginPlay();

	if (!BP_Item)
		return;

	UWorld * world = GetWorld();
	if (!world)
		return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	world->SpawnActor<AItemStore>(BP_Item, GetActorLocation(), GetActorRotation(), SpawnParams);
}

