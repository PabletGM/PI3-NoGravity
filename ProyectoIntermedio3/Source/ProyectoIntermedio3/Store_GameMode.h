#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Store_GameMode.generated.h"

class AItemStore;

UCLASS()
class PROYECTOINTERMEDIO3_API AStore_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AStore_GameMode();
	
	UFUNCTION()
	bool CanBuyItem(AItemStore* Item);

	void BuyItem(AItemStore* Item);

	// // Reference to the AudioManager
	// UPROPERTY(EditDefaultsOnly, Category = "Audio")
	// TSubclassOf<AAudioManager> BP_AudioManager;
	//
	// // Reference to the instantiated AudioManager
	// UPROPERTY()
	// AAudioManager* AudioManagerInstance;

private:
	int32 totalPealrsPlayer = 10;

	void InitializeAudioManager();
};
