#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PlayerStateProyectoIntermedio3.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPearlCountChanged, int32, NewPearlCount);

UCLASS()
class PROYECTOINTERMEDIO3_API APlayerStateProyectoIntermedio3 : public APlayerState
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnPearlCountChanged OnPearlCountChanged;

	UFUNCTION()
	void AddPearl(int32 value);

	UFUNCTION()
	int32 GetPearlCount() const { return totalPealrs; }

private:
	int32 totalPealrs = 0;

	class UGameInstanceNoGravity* GameInstance = nullptr;
};
