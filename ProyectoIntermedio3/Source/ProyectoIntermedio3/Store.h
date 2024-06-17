#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Store.generated.h"

UCLASS()
class PROYECTOINTERMEDIO3_API AStore : public AActor
{
	GENERATED_BODY()
	

public:	
	AStore();


protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
