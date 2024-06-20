// Fill out your copyright notice in the Description page of Project Settings.


#include "AIEnemyCharacterBase.h"

// Sets default values
AAIEnemyCharacterBase::AAIEnemyCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AAIEnemyCharacterBase::TakeDamage(float damageAmmount)
{
	CurrentHealth -= damageAmmount;

	if(damageAmmount >= CurrentHealth)
		Death();
}

void AAIEnemyCharacterBase::Death()
{
	// TODO Do whatever it needs to do before die

	this->Destroy();
}

// Called when the game starts or when spawned
void AAIEnemyCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	//AIType->GetValueAsName()

}

// Called every frame
void AAIEnemyCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAIEnemyCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

