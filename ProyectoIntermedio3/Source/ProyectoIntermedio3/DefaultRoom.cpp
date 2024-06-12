// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultRoom.h"

// Sets default values
ADefaultRoom::ADefaultRoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootCmp = CreateDefaultSubobject<USceneComponent>(TEXT("RootCmp"));
	SetRootComponent(RootCmp);

	NextRoomCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("NextRoomCollision"));
	NextRoomCollision->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADefaultRoom::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADefaultRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

