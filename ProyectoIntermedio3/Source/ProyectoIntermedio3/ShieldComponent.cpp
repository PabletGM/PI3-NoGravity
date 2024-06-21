#include "ShieldComponent.h"

#include "ProyectoIntermedio3Character.h"
#include "Kismet/GameplayStatics.h"

UShieldComponent::UShieldComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UShieldComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentShield = 0;
}

void UShieldComponent::SetFloaterVisibility(bool bVisibility)
{
	AProyectoIntermedio3Character* character = Cast<AProyectoIntermedio3Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if(character)
	{
		//look for static mesh component
		UStaticMeshComponent* Floater =Cast<UStaticMeshComponent>(character->GetDefaultSubobjectByName(TEXT("Floater")));
		if(Floater)
		{
			//put visibility
			Floater->SetVisibility(bVisibility);
		}
	}
}

void UShieldComponent::AddShield(int32 Amount)
{
	CurrentShield = FMath::Clamp(CurrentShield + Amount, 0, MaxShield);
	OnShieldChanged.Broadcast(CurrentShield);

	//TODO
	//call method that puts visible the staticMesh of Character that its call Floater
	SetFloaterVisibility(true);
}

void UShieldComponent::RemoveShield(int32 Amount)
{
	CurrentShield = FMath::Clamp(CurrentShield - Amount, 0, MaxShield);
	OnShieldChanged.Broadcast(CurrentShield);
	SetFloaterVisibility(false);
}


