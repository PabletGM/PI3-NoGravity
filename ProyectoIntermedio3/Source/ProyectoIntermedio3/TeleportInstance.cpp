#include "TeleportInstance.h"
#include "GameInstanceNoGravity.h" 
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CharacterStore.h"
#include "ItemStore.h"
#include "InventoryComponent.h"

ATeleportInstance::ATeleportInstance()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetCollisionProfileName("Trigger");
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ATeleportInstance::OnOverlapBegin);
	RootComponent = CollisionBox;
}

void ATeleportInstance::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
    if (OtherActor && (OtherActor != this) && OtherComp)
    {
        UGameInstanceNoGravity* GameInstance = Cast<UGameInstanceNoGravity>(UGameplayStatics::GetGameInstance(GetWorld()));
        if (GameInstance)
        {
           
            
        }

        if (LevelName != NAME_None)
        {
            UGameplayStatics::OpenLevel(this, LevelName);
        }
    }
}

