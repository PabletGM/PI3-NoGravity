// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultRoom.h"

// Sets default values
ADefaultRoom::ADefaultRoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
