
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

	int32 GetItemPrice() const { return ItemPrice; }
	FString GetItemName() const { return ItemName; }

public:	
	virtual void Interact_Implementation() override;
};
