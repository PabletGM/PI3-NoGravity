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
	
public:	
	ACollectable();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly) 
	UStaticMeshComponent* Mesh = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* Collider = nullptr;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
