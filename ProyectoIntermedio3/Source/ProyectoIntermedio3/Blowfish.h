#pragma once

#include "CoreMinimal.h"
#include "ItemStore.h"
#include "GameFramework/Actor.h"
#include "Blowfish.generated.h"

UCLASS()
class PROYECTOINTERMEDIO3_API ABlowfish : public AItemStore
{
	GENERATED_BODY()
	
public:	
	ABlowfish();

protected:
	virtual void BuyItem() override;
};
