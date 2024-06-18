#pragma once

#include "CoreMinimal.h"
#include "ItemInfoStruct.generated.h"

USTRUCT(BlueprintType)
struct FItemInfoStruct
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    FString ItemName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    float ItemPrice;

    FItemInfoStruct()
        : ItemName(TEXT("Default Item")), ItemPrice(0.0f)
    {
    }
};