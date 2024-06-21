#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenu_GameModeBase.generated.h"

class UItemDataAsset;

UCLASS()
class PROYECTOINTERMEDIO3_API AMainMenu_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
    AMainMenu_GameModeBase();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Items")
	UItemDataAsset* ItemDataAsset;
};
