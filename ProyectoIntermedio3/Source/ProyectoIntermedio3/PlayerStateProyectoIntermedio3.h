#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PlayerStateProyectoIntermedio3.generated.h"

class UGameInstanceNoGravity;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPearlCountChanged, int32, NewPearlCount);

UCLASS()
class PROYECTOINTERMEDIO3_API APlayerStateProyectoIntermedio3 : public APlayerState
{
	GENERATED_BODY()
	
public:
	APlayerStateProyectoIntermedio3();

	virtual void BeginPlay() override;

	//PEARLS
	UPROPERTY(BlueprintAssignable)
	FOnPearlCountChanged OnPearlCountChanged;

	UFUNCTION()
	void AddPearl(int32 value);

	UFUNCTION()
	int32 GetPearlCount() const { return totalPealrs; }

	void UpdateWidgetPearl();

private:
	int32 totalPealrs = 0;

	UGameInstanceNoGravity* GameInstance = nullptr;
};
