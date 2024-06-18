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
	TSubclassOf<ADefaultRoom> BP_Spawnable = nullptr;

	UPROPERTY(EditAnywhere)
	float ForwardSpawnOffset = 0;

	UPROPERTY()
	bool IsActive = true;

	UFUNCTION()
	void OnBeginBoxOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void AttemptSpawn(TSubclassOf<ADefaultRoom> RoomToSpawn);

	UPROPERTY()
	ADefaultRoom* NextRoom = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
