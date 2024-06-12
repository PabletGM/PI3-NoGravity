// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStore.h"

// Sets default values
ACharacterStore::ACharacterStore()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACharacterStore::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacterStore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterStore::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

