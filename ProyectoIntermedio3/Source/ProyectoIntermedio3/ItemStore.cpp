#include "ItemStore.h"
#include "Store.h"
#include "Store_GameMode.h"

AItemStore::AItemStore()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	SetRootComponent(Mesh);
}

FString AItemStore::GetInteractionText_Implementation()
{
	return FString::Printf(TEXT("Press [E] to buy %s for %d"), *ItemName, ItemPrice);
}

void AItemStore::Interact_Implementation()
{
    AStore_GameMode* GameMode = Cast<AStore_GameMode>(GetWorld()->GetAuthGameMode());

    if (GameMode)
    {
        GameMode->BuyItem(this);
    }
}

void AItemStore::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItemStore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
