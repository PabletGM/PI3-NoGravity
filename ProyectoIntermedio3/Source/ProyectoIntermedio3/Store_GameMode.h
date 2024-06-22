#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AudioManager.h"
#include "Store_GameMode.generated.h"

class AItemStore;
class AAudioManager;

UCLASS()
class PROYECTOINTERMEDIO3_API AStore_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AStore_GameMode();
	
	virtual void BeginPlay() override;

	UFUNCTION()
	bool CanBuyItem(AItemStore* Item);

	void BuyItem(AItemStore* Item);

	// Reference to the instantiated AudioManager
	UPROPERTY()
	AAudioManager* AudioManagerInstance;

	// Reference to the AudioManager
	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TSubclassOf<AAudioManager> BP_AudioManager;

	UFUNCTION()
	void MakeMusic(FString nameMusic);

	UFUNCTION()
	void MakeSoundEffect(FString nameSound);

protected:

	void InitializeAudioManager();

	void PostBeginPlay();

	

private:
	int32 totalPealrsPlayer = 0;


};
