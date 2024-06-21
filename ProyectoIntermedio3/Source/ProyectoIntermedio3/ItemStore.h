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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Items")
	UItemDataAsset* ItemDataAsset;

	virtual FString GetInteractionText_Implementation() override;

	int32 GetItemPrice() const;

	UTexture2D* GetItemIcon() const;

	virtual void BuyItem();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Items")
	int32 ItemIndex;

public:	
	virtual void Interact_Implementation() override;
};
