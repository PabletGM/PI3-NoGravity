#include "GameInstanceNoGravity.h"
#include "AudioManager.h"
#include "ItemStore.h"
#include "Kismet/GameplayStatics.h"

UGameInstanceNoGravity::UGameInstanceNoGravity()
{
	TotalPearls = 0;
}

void UGameInstanceNoGravity::SetInventoryIcons(TArray<UTexture2D*> Icons)
{
    InventoryIcons = Icons;
}

UTexture2D* UGameInstanceNoGravity::GetInventoryIcon(int32 Index) const
{
    if (Index >= 0 && Index < InventoryIcons.Num())
    {
        return InventoryIcons[Index];
    }
    return nullptr;
}

void UGameInstanceNoGravity::SetTotalPearls(int32 Value)
{
	TotalPearls = Value;
}


void UGameInstanceNoGravity::Init()
{
	Super::Init();

}




