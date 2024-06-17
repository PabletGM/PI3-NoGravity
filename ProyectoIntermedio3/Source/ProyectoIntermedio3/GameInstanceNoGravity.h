#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameInstanceNoGravity.generated.h"

UCLASS()
class PROYECTOINTERMEDIO3_API UGameInstanceNoGravity : public UGameInstance
{
	GENERATED_BODY()

public:
	UGameInstanceNoGravity();

	UFUNCTION()
	void SetTotalPearls(int32 Value);

	UFUNCTION()
	int32 GetTotalPearls() const { return TotalPearls; }

protected:
	UPROPERTY()
	int32 TotalPearls;
};