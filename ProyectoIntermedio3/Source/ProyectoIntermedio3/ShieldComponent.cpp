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
}

void UShieldComponent::RemoveShield(int32 Amount)
{
	CurrentShield = FMath::Clamp(CurrentShield - Amount, 0, MaxShield);
}

void UShieldComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FString ShieldText = FString::Printf(TEXT("CurrentShield: %d"), CurrentShield);
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, ShieldText);
}

