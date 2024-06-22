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

UCLASS()
class PROYECTOINTERMEDIO3_API UGameInstanceNoGravity : public UGameInstance
{
	GENERATED_BODY()

public:
	UGameInstanceNoGravity();

	FPlayerData GetPlayerData() { return PlayerData; }

	//INVENTORY
	void RestoreInventoryIcons(UInventoryComponent* InventoryComponent);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Items")
	UItemDataAsset* ItemDataAsset = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player")
	FPlayerData PlayerData;

	//PEARLS
	UFUNCTION()
	void SetTotalPearls(int32 Value);

	UFUNCTION()
	int32 GetTotalPearls() { return TotalPearls; }

protected:
	UPROPERTY()
	int32 TotalPearls;
};
