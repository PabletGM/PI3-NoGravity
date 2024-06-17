
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameOverManager.generated.h"

class UGameOver;

UCLASS()
class PROYECTOINTERMEDIO3_API AGameOverManager : public AActor
{
	GENERATED_BODY()
	
public:    
	AGameOverManager();

	UFUNCTION(BlueprintCallable, Category="GameOver")
	void ShowGameOverMenu();

protected:
	virtual void BeginPlay() override;

public:    
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category="UI")
	TSubclassOf<UUserWidget> GameOverMenuClass;

	UPROPERTY()
	UGameOver* GameOverWidget;
};
