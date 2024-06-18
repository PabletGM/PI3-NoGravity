// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomSpawner.h"

#include "DefaultRoom.h"
#include "ProyectoIntermedio3Character.h"
#include "Logging/StructuredLog.h"

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
			if(IsActive)
			{
				if (IsFirstSpawner)
					HasSplit = false;

				UE_LOGFMT(LogTemp, Log, "{0}", HasSplit);
				//if it has a set room to spawn it spawns that, or if it cant it spawns a room with no doors
				if(BP_Spawnable != nullptr)
				{
					if(!AttemptSpawn(BP_Spawnable))
					{
						AttemptSpawn(BP_NoDoorRoom);
					}
				}
					
				else
				{
					//random to try to make a 2 door room
					int randomSplit = FMath::RandRange(0, 3);

					if(randomSplit == 0 && !HasSplit && BP_TwoDoorRooms.Num() > 0)
					{
						int randomSplitRoom = FMath::RandRange(0, BP_TwoDoorRooms.Num() - 1);
						int firstRandomRoom = randomSplitRoom;
						while (true)
						{
							if (!AttemptSpawn(BP_TwoDoorRooms[randomSplitRoom]))
							{
								randomSplitRoom += 1;
								if (randomSplitRoom > BP_TwoDoorRooms.Num() - 1)
								{
									randomSplitRoom = 0;
								}
								if (randomSplitRoom == firstRandomRoom)
								{
									DidntSpawnSplitRoom = true;
									break;
								}
							}
							else
							{
								HasSplit = true;
								DidntSpawnSplitRoom = false;
								break;
							}
						}
					}

					if(DidntSpawnSplitRoom)
					{
						int randomRoom = FMath::RandRange(0, BP_OneDoorRooms.Num() - 1);
						int firstRandomRoom = randomRoom;
						while (true)
						{
							if (!AttemptSpawn(BP_OneDoorRooms[randomRoom]))
							{
								randomRoom += 1;
								if (randomRoom > BP_OneDoorRooms.Num() - 1)
								{
									randomRoom = 0;
								}
								if (randomRoom == firstRandomRoom)
								{
									AttemptSpawn(BP_NoDoorRoom);
									break;
								}
							}
							else
							{
								break;
							}
						}
					}
					DidntSpawnSplitRoom = true;
				}
			}
				
		}
	}
}

bool ARoomSpawner::AttemptSpawn(TSubclassOf<ADefaultRoom> RoomToSpawn)
{
	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		// Temporary Spawn Params

		FVector ForwardVector = GetActorForwardVector();

		FVector Location = GetActorLocation() + ForwardVector * ForwardSpawnOffset;
		FRotator Rotation = GetActorRotation();

		ADefaultRoom* MyRoom = World->SpawnActor<ADefaultRoom>(RoomToSpawn, Location, Rotation, SpawnParams);
		if(!MyRoom->IsSpawnable)
		{
			World->DestroyActor(MyRoom);
			UE_LOG(LogTemp, Log, TEXT("Room Can't Spawn Here"));
			return false;
		}
		else
		{
			IsActive = false;
			UE_LOG(LogTemp, Log, TEXT("Room Spawned"));
			return true;
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("No World"));
		return false;
	}
}
