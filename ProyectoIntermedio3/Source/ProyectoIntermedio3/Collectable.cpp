#include "Collectable.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/Engine.h"

ACollectable::ACollectable()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	SetRootComponent(Mesh);

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetupAttachment(Mesh);
	Collider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collider->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	Collider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ACollectable::OnOverlapBegin);
}

void ACollectable::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Collectable picked up!"));
}

void ACollectable::BeginPlay()
{
	Super::BeginPlay();
}


