#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectable.h"

#include "Oxygen.generated.h"

UCLASS()
class PROYECTOINTERMEDIO3_API AOxygen : public ACollectable
{
	GENERATED_BODY()
	
public:	
	AOxygen();

	virtual void Collected(class AActor* Collector) override;
};
