
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"

#include "ItemStore.generated.h"

class UStaticMeshComponent;

UCLASS()
class PROYECTOINTERMEDIO3_API AItemStore : public AActor, public IInteractable
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "StoreItem")
	FString ItemName;

	UPROPERTY(EditDefaultsOnly, Category = "StoreItem")
	int32 ItemPrice;

public:	
	AItemStore();

	virtual FString GetInteractionText_Implementation() override;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation() override;
};
