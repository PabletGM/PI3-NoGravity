#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PlayerStateProyectoIntermedio3.generated.h"

UCLASS()
class PROYECTOINTERMEDIO3_API APlayerStateProyectoIntermedio3 : public APlayerState
{
	GENERATED_BODY()
	
public:

	UFUNCTION()
	void AddPearl(int32 value);

private:
	int32 totalPealrs = 0;
};
