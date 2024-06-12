// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomSpawner.h"

#include "DefaultRoom.h"
#include "ProyectoIntermedio3Character.h"

// Sets default values
ARoomSpawner::ARoomSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootCmp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(RootCmp);

	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionMesh->SetupAttachment(RootCmp);
	CollisionMesh->SetGenerateOverlapEvents(true);
	CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &ARoomSpawner::OnBeginBoxOverlap);
}

// Called when the game starts or when spawned
void ARoomSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoomSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARoomSpawner::OnBeginBoxOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		AProyectoIntermedio3Character* character = Cast<AProyectoIntermedio3Character>(OtherActor);
		if (character)
		{
			AttemptSpawn(BP_Spawnable);
		}
	}
}

void ARoomSpawner::SpawnRoom()
{
	if(BP_Spawnable)
	{
		UWorld* World = GetWorld();
		if(World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			// Temporary Spawn Params

			FVector ForwardVector = GetActorForwardVector();
			
			FVector Location = GetActorLocation() + ForwardVector * ForwardSpawnOffset;
			FRotator Rotation = GetActorRotation();

			World->SpawnActor<ADefaultRoom>(ADefaultRoom::StaticClass(), Location, Rotation, SpawnParams);
		}
	}
}

void ARoomSpawner::AttemptSpawn(TSubclassOf<ADefaultRoom> RoomToSpawn)
{
	UWorld* World = GetWorld();
	if (World)
	{
		ADefaultRoom* MyRoom = RoomToSpawn->GetDefaultObject<ADefaultRoom>();
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		// Temporary Spawn Params

		FVector ForwardVector = GetActorForwardVector();

		FVector Location = GetActorLocation() + ForwardVector * ForwardSpawnOffset;
		FRotator Rotation = GetActorRotation();

		MyRoom = World->SpawnActor<ADefaultRoom>(RoomToSpawn, Location, Rotation, SpawnParams);
		if(!MyRoom->IsSpawnable)
		{
			World->DestroyActor(MyRoom);
		}
	}
}
