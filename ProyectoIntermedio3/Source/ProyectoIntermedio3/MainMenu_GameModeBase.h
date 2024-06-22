#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlayerDataStruct.h"
#include "ItemInfoStruct.h"
#include "AudioManager.h"
#include "MainMenu_GameModeBase.generated.h"

class UItemDataAsset;
class AAudioManager;
class UPlayerDataAsset;

UCLASS()
class PROYECTOINTERMEDIO3_API AMainMenu_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
    AMainMenu_GameModeBase();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Items")
	UPlayerDataAsset* PlayerDataAsset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Items")
	UItemDataAsset* ItemDataAsset;

	// Reference to the instantiated AudioManager
	UPROPERTY()
	AAudioManager* AudioManagerInstance;

	// Reference to the AudioManager
	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TSubclassOf<AAudioManager> BP_AudioManager;

	UFUNCTION()
	void MakeMusic(FString nameMusic);

	UFUNCTION()
	void MakeSoundEffect1(FString nameSound);

	

protected:
	void InitializeAudioManager();

	void PostBeginPlay();
	
private:
	void ResetPlayer();
};
