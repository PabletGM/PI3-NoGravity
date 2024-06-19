#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"

#include "ItemInfoStruct.generated.h"

USTRUCT(BlueprintType)
struct FItemInfoStruct
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    FString ItemName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    FString Description;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    float ItemPrice;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    UTexture2D* ItemIcon;

    FItemInfoStruct()
        : ItemName(TEXT("Default Item")), ItemPrice(0.0f), ItemIcon(nullptr)
    {
    }
};