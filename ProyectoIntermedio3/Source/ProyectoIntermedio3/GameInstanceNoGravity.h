#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameFramework/Actor.h"
#include "GameInstanceNoGravity.generated.h"

class AProyectoIntermedio3Character;

UCLASS()
class PROYECTOINTERMEDIO3_API UGameInstanceNoGravity : public UGameInstance
{
	GENERATED_BODY()

public:
	UGameInstanceNoGravity();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
	AProyectoIntermedio3Character* PlayerCharacter;

	UFUNCTION()
	void SetTotalPearls(int32 Value);

	UFUNCTION()
	int32 GetTotalPearls() const { return TotalPearls; }

protected:
	UPROPERTY()
	int32 TotalPearls;

	UFUNCTION()
	virtual void Init() override;
};
