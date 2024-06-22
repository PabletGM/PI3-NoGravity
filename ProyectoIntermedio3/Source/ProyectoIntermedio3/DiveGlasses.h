#pragma once
#include "CoreMinimal.h"
#include "ItemStore.h"
#include "GameFramework/Actor.h"
#include "DiveGlasses.generated.h"

class AItemStore;
UCLASS()
class PROYECTOINTERMEDIO3_API ADiveGlasses : public AItemStore
{
	GENERATED_BODY()
	
public:	
	ADiveGlasses();

protected:
	virtual void BuyItem() override;

};
