#include "OxygenComponent.h"

UOxygenComponent::UOxygenComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UOxygenComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentOxygen = MaxOxygen;
}

void UOxygenComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TimeSinceLastDecrease += DeltaTime;

	if (TimeSinceLastDecrease >= TimeBetweenDecreases)
	{
		DecreaseOxygen();
		TimeSinceLastDecrease = 0.0f; 
	}
}

void UOxygenComponent::DecreaseOxygen()
{
	CurrentOxygen -= OxygenDecrement;
	CurrentOxygen = FMath::Clamp(CurrentOxygen, 0.0f, MaxOxygen);

	OnOxygenChanged.Broadcast(CurrentOxygen, MaxOxygen);
}

void UOxygenComponent::SetCurrentOxygen(int32 NewOxygen)
{
	if (CurrentOxygen != MaxOxygen)
	{
		CurrentOxygen = FMath::Clamp(NewOxygen, 0, MaxOxygen);

		OnOxygenChanged.Broadcast(CurrentOxygen, MaxOxygen);
	}
}