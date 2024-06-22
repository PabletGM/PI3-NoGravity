#pragma once

#include "CoreMinimal.h"
#include "ItemStore.h"
#include "GameFramework/Actor.h"
#include "TinCan.generated.h"

class AItemStore;
UCLASS()
class PROYECTOINTERMEDIO3_API ATinCan : public AItemStore
{
	GENERATED_BODY()
	
public:	
	ATinCan();

protected:
	virtual void BuyItem() override;
};
