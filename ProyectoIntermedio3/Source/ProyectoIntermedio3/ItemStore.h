#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "ItemDataAsset.h"
#include "PlayerDataAsset.h"

#include "ItemStore.generated.h"

class UStaticMeshComponent;
class UTextRenderComponent;
class UGameInstanceNoGravity;
class UPlayerDataAsset;

UCLASS()
class PROYECTOINTERMEDIO3_API AItemStore : public AActor, public IInteractable
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UTextRenderComponent* TextRenderComponent = nullptr;

public:	
	AItemStore();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Items")
	UItemDataAsset* ItemDataAsset;

	virtual FString GetInteractionText_Implementation() override;

	virtual FString GetDescriptionText_Implementation() override;

	int32 GetItemPrice() const;

	UTexture2D* GetItemIcon() const;

	virtual void BuyItem();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Items")
	int32 ItemIndex = 0;

	UGameInstanceNoGravity* GameInstance = nullptr;

public:	
	virtual void Interact_Implementation() override;
};
