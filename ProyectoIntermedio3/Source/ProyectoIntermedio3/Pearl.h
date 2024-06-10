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

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
