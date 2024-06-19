// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultRoom.h"

// Sets default values
ADefaultRoom::ADefaultRoom()
{
	PrimaryActorTick.bCanEverTick = false;

	RootCmp = CreateDefaultSubobject<USceneComponent>(TEXT("RootCmp"));
	SetRootComponent(RootCmp);

	FirstNextRoomCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("NextRoomCollision1"));
	FirstNextRoomCollision->SetupAttachment(RootComponent);

	SecondNextRoomCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("NextRoomCollision2"));
	SecondNextRoomCollision->SetupAttachment(RootComponent);

	ThirdNextRoomCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("NextRoomCollision3"));
	ThirdNextRoomCollision->SetupAttachment(RootComponent);

	FirstNextRoomCollision->OnComponentBeginOverlap.AddDynamic(this, &ADefaultRoom::OnBeginFirstBoxOverlap);
	SecondNextRoomCollision->OnComponentBeginOverlap.AddDynamic(this, &ADefaultRoom::OnBeginSecondBoxOverlap);
	ThirdNextRoomCollision->OnComponentBeginOverlap.AddDynamic(this, &ADefaultRoom::OnBeginThirdBoxOverlap);
}

void ADefaultRoom::BeginPlay()
{
	Super::BeginPlay();
}


//if a collision of the doors is colliding with another room, it means it cannot be spawned
void ADefaultRoom::CheckOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		ADefaultRoom* room = Cast<ADefaultRoom>(OtherActor);
		if (room == this)
			return;

		if (room)
		{
			IsSpawnable = false;
		}
	}
}

//upon spawning the room, it will check if any of the 3 possible doors will lead to a room, which means this room is not available because it will have a door going into an already existing room

//we divide the 3 possible doors because there are rooms that have less than 3 doors, and we will check if the collisions are used or not, to avoid possible conflicts
void ADefaultRoom::OnBeginFirstBoxOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(NumberOfDoors >= 1)
		CheckOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void ADefaultRoom::OnBeginSecondBoxOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (NumberOfDoors >= 2)
	CheckOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void ADefaultRoom::OnBeginThirdBoxOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (NumberOfDoors >= 3)
	CheckOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}
