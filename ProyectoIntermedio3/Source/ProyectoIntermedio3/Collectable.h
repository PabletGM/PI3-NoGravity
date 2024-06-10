#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectable.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class PROYECTOINTERMEDIO3_API ACollectable : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* Collider = nullptr;

public:	
	ACollectable();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

	virtual void Collected(class AActor* Collector);
};
