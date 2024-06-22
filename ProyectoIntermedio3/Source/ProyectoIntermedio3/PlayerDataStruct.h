#pragma once

#include "CoreMinimal.h"

#include "PlayerDataStruct.generated.h"

USTRUCT(BlueprintType)
struct FPlayerData
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float MaxWalkSpeed;  

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 PlayerLevel; 

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 CurrentShield;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 MaxOxygen;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float OxygenDecrement;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 CapacityInventory;

    FPlayerData()
        : MaxWalkSpeed(500.0f) 
        , PlayerLevel(1)
        , CurrentShield(0)
        , MaxOxygen(100)
        , OxygenDecrement(0.5f)
        , CapacityInventory(6)
    {
    }
};
