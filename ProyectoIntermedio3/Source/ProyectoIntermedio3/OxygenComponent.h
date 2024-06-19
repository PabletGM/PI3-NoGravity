#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OxygenComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnOxygenChanged, int32, cur, int32, max);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROYECTOINTERMEDIO3_API UOxygenComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UOxygenComponent();

	UPROPERTY()
	FOnOxygenChanged OnOxygenChanged;

	UPROPERTY()
	int CurrentOxygen;

	UPROPERTY(EditDefaultsOnly)
	int MaxOxygen = 100;

	UPROPERTY(EditDefaultsOnly)
	float OxygenDecrement = 0.5f;

	int32 GetOxygen() const { return CurrentOxygen; }

	void SetCurrentOxygen(int32 NewOxygen);

	void AddOxygen(float Amount);

	void Death();

protected:
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float TimeSinceLastDecrease = 0.0f;
	float TimeBetweenDecreases = 1.5f;

	bool canDie = true;
	void DecreaseOxygen();
};
