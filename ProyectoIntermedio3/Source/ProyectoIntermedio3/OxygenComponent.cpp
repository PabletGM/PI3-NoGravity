#include "OxygenComponent.h"

#include "MainWidget.h"
#include "Proyecto3PlayerController.h"
#include "ProyectoIntermedio3Character.h"

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

	Death();
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

void UOxygenComponent::Death()
{
	if(canDie)
	{
		if(CurrentOxygen > 0)
			return;
	
		auto* owner = Cast<AProyectoIntermedio3Character>(GetOwner());

		//call death function
		owner->DeathPlayer();
		
		//quit access to canDie
		canDie = false;
		
		if(!owner)
		{
			return;
		}

		auto* controller = Cast<AProyecto3PlayerController>(owner->GetController());
		controller->bShowMouseCursor = true;

		if(!controller)
		{
			return;
		}
	
		controller->MainWidget->ShowConcreteWidget(controller->MainWidget->GameOverWidget);
	}
	
}
