#include "TeleportInstance.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

ATeleportInstance::ATeleportInstance()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetCollisionProfileName("Trigger");
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ATeleportInstance::OnOverlapBegin);
	RootComponent = CollisionBox;
}

// Called when the game starts or when spawned
void ATeleportInstance::BeginPlay()
{
	Super::BeginPlay();    
}

// Called every frame
void ATeleportInstance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATeleportInstance::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (LevelName != NAME_None)
		{
			UGameplayStatics::OpenLevel(this, LevelName);
		}
	}
}

