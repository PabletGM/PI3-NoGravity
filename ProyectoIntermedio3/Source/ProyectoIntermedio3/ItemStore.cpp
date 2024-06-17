#include "ItemStore.h"
#include "Store.h"

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
    if (Store)
    {
        Store->BuyItem(this);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AItemStore::Interact_Implementation - Store reference is not set!"));
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
