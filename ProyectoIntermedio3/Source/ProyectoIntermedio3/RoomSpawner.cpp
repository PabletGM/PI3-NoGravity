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

//when player enters the door to a next room
void ARoomSpawner::OnBeginBoxOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//check if its the player
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		AProyectoIntermedio3Character* character = Cast<AProyectoIntermedio3Character>(OtherActor);
		if (character)
		{
			//only spawn a room once, otherwise they overlap on top of eachother
			if(IsActive)
			{
				//we do this to reset HasSplit because it's a static bool
				if (IsFirstSpawner)
					HasSplit = false;

				UE_LOGFMT(LogTemp, Log, "Map has a split?: {0}", HasSplit);

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

					//if we hit the random, we spawn a two door room
					if(randomSplit == 0 && !HasSplit && BP_TwoDoorRooms.Num() > 0)
					{
						//we check which room we spawn
						int randomSplitRoom = FMath::RandRange(0, BP_TwoDoorRooms.Num() - 1);
						int firstRandomRoom = randomSplitRoom;

						//while true so it will cycle through all of the doors in case the door you try to spawn can't spawn there.
						//Example -> tries to spawn room 1, can't spawn room one -> tries to spawn room 2 -> can spawn room 2 -> spawns room 2
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
									SpawnedSplitRoom = false;
									break;
								}
							}
							//correctly spawned two door room, so now we have a split
							else
							{
								HasSplit = true;
								SpawnedSplitRoom = true;
								break;
							}
						}
					}

					//we check if we already ran the code above
					if(!SpawnedSplitRoom)
					{
						//if we already have a split on the map, we won't spawn another split room until one of the paths closes, so we roll a dice to try to spawn a 0 door room
						if(HasSplit)
						{
							int randomZeroRoom = FMath::RandRange(0, 3);
							if(randomZeroRoom == 0)
							{
								HasSplit = false;
								AttemptSpawn(BP_NoDoorRoom);
								return;
							}
						}

						//random to check which room we spawn
						int randomRoom = FMath::RandRange(0, BP_OneDoorRooms.Num() - 1);
						int firstRandomRoom = randomRoom;

						//similar to above, we choose one room but if it can't spawn we cycle through the rest until one of them spawns
						while (true)
						{
							if (!AttemptSpawn(BP_OneDoorRooms[randomRoom]))
							{
								randomRoom += 1;
								if (randomRoom > BP_OneDoorRooms.Num() - 1)
								{
									randomRoom = 0;
								}

								//if no room can spawn it means we have to spawn a 0 door room
								if (randomRoom == firstRandomRoom)
								{
									// if there is another path, we spawn a dead end room
									if(HasSplit)
									{
										AttemptSpawn(BP_NoDoorRoom);
										HasSplit = false;
									}

									//if there is no other path, we need to spawn the final room of the level
									else
									{
										AttemptSpawn(BP_FinalRoom);
									}
									break;
								}
							}
							else
							{
								break;
							}
						}
					}
					SpawnedSplitRoom = false;
				}
			}
				
		}
	}
}

//to try to spawn rooms
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

		//we spawn the room and save it into a variable, no matter if it can or can't spawn
		ADefaultRoom* MyRoom = World->SpawnActor<ADefaultRoom>(RoomToSpawn, Location, Rotation, SpawnParams);

		//we check if the room is spawnable. The room will check on BeginPlay if it's colliding with something, and then we use that information here

		//if the room is not spawnable, we destroy it and return FALSE, which we can use to know that the room has not been spawned
		if(!MyRoom->IsSpawnable)
		{
			World->DestroyActor(MyRoom);
			UE_LOG(LogTemp, Log, TEXT("Room Can't Spawn Here"));
			return false;
		}

		//otherwise, we spawn the room and we turn off the spawner, so it doesn't spawns more rooms
		else
		{
			IsActive = false;
			UE_LOG(LogTemp, Log, TEXT("Room Spawned"));
			return true;
		}
	}

	//vs code was saying there was a possibility that the function didn't return a bool ;)
	else
	{
		UE_LOG(LogTemp, Log, TEXT("No World"));
		return false;
	}
}
