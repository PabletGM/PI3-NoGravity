#pragma once

#include "CoreMinimal.h"
#include "Collectable.h"
#include "GameFramework/Actor.h"

#include "Shield.generated.h"

UCLASS()
class PROYECTOINTERMEDIO3_API AShield : public ACollectable
{
	GENERATED_BODY()
	
public:	
	AShield();

	virtual void Collected(class AActor* Collector) override;
};
