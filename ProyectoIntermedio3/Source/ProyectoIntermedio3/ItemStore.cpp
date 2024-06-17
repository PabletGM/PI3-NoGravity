#include "ItemStore.h"

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
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "BUY");
}


void AItemStore::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItemStore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
