#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectable.h"
#include "Pearl.generated.h"

UCLASS()
class PROYECTOINTERMEDIO3_API APearl : public ACollectable
{
	GENERATED_BODY()
	
public:	
	APearl();

	virtual void Collected(class AActor* Collector) override;

	UPROPERTY(EditDefaultsOnly)
	int32 pearlValue = 1;

};
