#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AudioManager.h"
#include "MainMenu_GameModeBase.generated.h"

class UItemDataAsset;
class AAudioManager;

UCLASS()
class PROYECTOINTERMEDIO3_API AMainMenu_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
    AMainMenu_GameModeBase();

	virtual void BeginPlay() override;

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

protected:

	void InitializeAudioManager();

	void PostBeginPlay();
};
