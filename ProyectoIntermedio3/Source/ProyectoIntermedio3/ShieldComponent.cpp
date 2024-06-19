#include "ShieldComponent.h"

UShieldComponent::UShieldComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UShieldComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentShield = 0;
}

void UShieldComponent::AddShield(int32 Amount)
{
	CurrentShield = FMath::Clamp(CurrentShield + Amount, 0, MaxShield);
	OnShieldChanged.Broadcast(CurrentShield);
}

void UShieldComponent::RemoveShield(int32 Amount)
{
	CurrentShield = FMath::Clamp(CurrentShield - Amount, 0, MaxShield);
	OnShieldChanged.Broadcast(CurrentShield);
}


