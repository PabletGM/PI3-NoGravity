#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Store.generated.h"

class UStaticMeshComponent;

UCLASS()
class PROYECTOINTERMEDIO3_API AStore : public AActor, public IInteractable
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh = nullptr;

public:	
	AStore();

	virtual FString GetInteractionText_Implementation() override;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation() override;
};
