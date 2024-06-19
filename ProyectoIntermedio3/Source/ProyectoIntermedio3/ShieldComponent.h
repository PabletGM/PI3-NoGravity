#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShieldComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShieldChanged, int32, NewShieldValue);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROYECTOINTERMEDIO3_API UShieldComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UShieldComponent();

	UPROPERTY()
	FOnShieldChanged OnShieldChanged;

	UPROPERTY()
	int CurrentShield;

	UPROPERTY(EditDefaultsOnly)
	int MaxShield = 3;

	int32 GetShield() const { return CurrentShield; }

	UFUNCTION()
	void AddShield(int32 Amount);

	UFUNCTION()
	void RemoveShield(int32 Amount);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
};
