#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameFramework/Actor.h"
#include "GameInstanceNoGravity.generated.h"

class AItemStore;

UCLASS()
class PROYECTOINTERMEDIO3_API UGameInstanceNoGravity : public UGameInstance
{
	GENERATED_BODY()

public:
	UGameInstanceNoGravity();

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	TArray<UTexture2D*> InventoryIcons;

	UFUNCTION(BlueprintCallable)
	void SetInventoryIcons(TArray<UTexture2D*> Icons);

	UFUNCTION(BlueprintCallable)
	UTexture2D* GetInventoryIcon(int32 Index) const;

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
