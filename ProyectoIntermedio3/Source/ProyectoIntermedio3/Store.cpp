#include "Store.h"
#include "Components/StaticMeshComponent.h"

AStore::AStore()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	SetRootComponent(Mesh);
}

FString AStore::GetInteractionText_Implementation()
{
	return "Press [E] to trade with the Captain";
}

void AStore::Interact_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "DETECT");
}

void AStore::BeginPlay()
{
	Super::BeginPlay();
	
}

void AStore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

