#include "TinCan.h"
#include "ProyectoIntermedio3Character.h"

ATinCan::ATinCan()
{
	PrimaryActorTick.bCanEverTick = true;
}

/*void ATinCan::BuyItem()
{
	Super::BuyItem();

	UE_LOG(LogTemp, Log, TEXT("Interacting with TinCan!"));

	AProyectoIntermedio3Character* PlayerCharacter = Cast<AProyectoIntermedio3Character>(GetWorld()->GetFirstPlayerController()->GetCharacter());

	if (PlayerCharacter)
	{
		PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed += 100.0f;
	}

}*/
