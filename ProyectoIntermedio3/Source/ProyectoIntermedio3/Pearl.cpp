#include "Pearl.h"
#include "PlayerStateProyectoIntermedio3.h"

APearl::APearl()
{
	PrimaryActorTick.bCanEverTick = true;

}

void APearl::BeginPlay()
{
	Super::BeginPlay();
}

void APearl::Collected(AActor* Collector)
{
	APlayerController* PlayerController = Cast<APlayerController>(Collector->GetInstigatorController());

	if (PlayerController)
	{
		APlayerState* PlayerState = PlayerController->GetPlayerState<APlayerState>();

		APlayerStateProyectoIntermedio3* MyPlayerState = Cast<APlayerStateProyectoIntermedio3>(PlayerState);

		if (MyPlayerState)
		{
			MyPlayerState->AddPearl(pearlValue);
		}
	}
}