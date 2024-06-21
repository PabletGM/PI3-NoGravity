
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GameFramework/Actor.h"
#include "Enemy.h"
#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"

#include "EnemySpawner.generated.h"

UCLASS()
class PROYECTOINTERMEDIO3_API AEnemySpawner : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* RootCmp = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UArrowComponent* ArrowCmp = nullptr;

	UPROPERTY(EditDefaultsOnly)
	USphereComponent* SpawnSphere = nullptr;

	
public:	
	AEnemySpawner();

	UPROPERTY(EditAnywhere)
	TSubclassOf<ACharacter> BP_Enemy = nullptr;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AAIController> BP_EnemyController = nullptr;

protected:
	virtual void BeginPlay() override;

};