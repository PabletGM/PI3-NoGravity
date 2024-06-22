#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemStore.h"
#include "StoreItemSpawner.generated.h"

UCLASS()
class PROYECTOINTERMEDIO3_API AStoreItemSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AStoreItemSpawner();

	UPROPERTY(EditAnywhere)
	TSubclassOf<AItemStore> BP_Item = nullptr;

protected:
	virtual void BeginPlay() override;

};
