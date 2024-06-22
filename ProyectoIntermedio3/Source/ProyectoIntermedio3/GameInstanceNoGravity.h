#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameFramework/Actor.h"
#include "ItemStore.h"
#include "PlayerDataStruct.h"
#include "GameInstanceNoGravity.generated.h"

class AProyectoIntermedio3Character;
class UInventoryComponent;
class UItemDataAsset;
class UPlayerDataAsset;

UCLASS()
class PROYECTOINTERMEDIO3_API UGameInstanceNoGravity : public UGameInstance
{
	GENERATED_BODY()

public:
	UGameInstanceNoGravity();

	//PLAYER
	UPlayerDataAsset* GetPlayerData() { return PlayerDataAsset; }

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Items")
	UPlayerDataAsset* PlayerDataAsset = nullptr;

	//INVENTORY
	void RestoreInventoryIcons(UInventoryComponent* InventoryComponent);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Items")
	UItemDataAsset* ItemDataAsset = nullptr;

	//PEARLS
	UFUNCTION()
	void SetTotalPearls(int32 Value);

	UFUNCTION()
	int32 GetTotalPearls() { return TotalPearls; }

protected:
	UPROPERTY()
	int32 TotalPearls;
};
