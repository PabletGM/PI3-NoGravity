#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemInfoStruct.h"

#include "ItemDataAsset.generated.h"

UCLASS()
class PROYECTOINTERMEDIO3_API UItemDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Items")
	TArray<FItemInfoStruct> Items;
};
