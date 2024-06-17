#include "Store.h"
#include "ItemStore.h"
#include "PlayerStateProyectoIntermedio3.h"
#include "GameInstanceNoGravity.h"

AStore::AStore()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AStore::BuyItem(AItemStore* Item)
{
	if (!Item)
	{
		return;
	}

	UGameInstanceNoGravity* GameInstance = Cast<UGameInstanceNoGravity>(GetGameInstance());
	
	if (GameInstance->GetTotalPearls() >= Item->GetItemPrice())
	{
		GameInstance->SetTotalPearls(GameInstance->GetTotalPearls() - Item->GetItemPrice());

		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("You bought %s!"), *Item->GetItemName()));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("0 money"));
	}
}

void AStore::BeginPlay()
{
	Super::BeginPlay();
}

void AStore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

