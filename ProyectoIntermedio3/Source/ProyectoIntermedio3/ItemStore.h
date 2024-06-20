
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "ItemDataAsset.h"

#include "ItemStore.generated.h"

class UStaticMeshComponent;

UCLASS()
class PROYECTOINTERMEDIO3_API AItemStore : public AActor, public IInteractable
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh = nullptr;

public:	
	AItemStore();

	UFUNCTION(BlueprintCallable, Category = "Items")
	virtual void InitializeItem();

	virtual FString GetInteractionText_Implementation() override;

	int32 GetItemPrice() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Items")
	int32 ItemIndex;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Items")
	UItemDataAsset* ItemDataAsset;

public:	
	virtual void Interact_Implementation() override;

    //void BuyItem() override;
};
