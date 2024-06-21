#include "Collectable.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "ProyectoIntermedio3Character.h"

#include "Engine/Engine.h"

ACollectable::ACollectable()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	SetRootComponent(Mesh);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetupAttachment(Mesh);
	Collider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collider->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	Collider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	Collider->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
}

void ACollectable::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ACollectable::OnOverlapBegin);
}


void ACollectable::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this))
	{
		AProyectoIntermedio3Character* myCharacter = Cast<AProyectoIntermedio3Character>(OtherActor);
		if (myCharacter)
		{
			Collected(OtherActor);
			Destroy();
		}
	}
}

void ACollectable::Collected(AActor* Collector)
{

}

