
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"

#include "ItemStore.generated.h"

class UStaticMeshComponent;
class AStore;

UCLASS()
class PROYECTOINTERMEDIO3_API AItemStore : public AActor, public IInteractable
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "StoreItem")
	FString ItemName = "ha";

	UPROPERTY(EditDefaultsOnly, Category = "StoreItem")
	int32 ItemPrice = 3;

public:	
	AItemStore();

	virtual FString GetInteractionText_Implementation() override;

	int32 GetItemPrice() const { return ItemPrice; }
	FString GetItemName() const { return ItemName; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Store")
	AStore* Store;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation() override;
};
