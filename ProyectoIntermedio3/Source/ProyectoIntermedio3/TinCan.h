#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemStore.h"

#include "TinCan.generated.h"

UCLASS()
class PROYECTOINTERMEDIO3_API ATinCan : public AItemStore
{
	GENERATED_BODY()
	
public:	
	ATinCan();

protected:
	virtual void BuyItem() override;
};
