// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"

#include "RoomSpawner.generated.h"

class ADefaultRoom;
UCLASS()
class PROYECTOINTERMEDIO3_API ARoomSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoomSpawner();

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* CollisionMesh = nullptr;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* RootCmp = nullptr;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ADefaultRoom> BP_Room = nullptr;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ADefaultRoom>> BP_OneDoorRooms = {};

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ADefaultRoom>> BP_TwoDoorRooms = {};

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ADefaultRoom> BP_NoDoorRoom = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ADefaultRoom> BP_FinalRoom = nullptr;

	inline static bool HasSplit = false;

	inline static int TotalRoomsSpawned = 0;

	inline static int TotalRoomsSinceSplit = 0;

	UPROPERTY(EditAnywhere)
	float ForwardSpawnOffset = 0;

	UPROPERTY()
	bool IsActive = true;

	UPROPERTY()
	bool SpawnedSplitRoom = false;

	UPROPERTY(EditAnywhere)
	bool IsFirstSpawner = false;

	UPROPERTY(EditAnywhere)
	bool IsFinalSpawner = false;

	UFUNCTION()
	void FinalSpawnerImplementation(TSubclassOf<ADefaultRoom> RoomToSpawn);

	UFUNCTION()
	void OnBeginBoxOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	bool AttemptSpawn(TSubclassOf<ADefaultRoom> RoomToSpawn);

	UPROPERTY()
	ADefaultRoom* NextRoom = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
