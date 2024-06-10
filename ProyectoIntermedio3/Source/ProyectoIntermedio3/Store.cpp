#include "Store.h"
#include "Components/StaticMeshComponent.h"

AStore::AStore()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	SetRootComponent(Mesh);
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

