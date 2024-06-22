#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PlayerDataStruct.h"

#include "PlayerDataAsset.generated.h"

UCLASS()
class PROYECTOINTERMEDIO3_API UPlayerDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player")
	FPlayerData PlayerData;
};
