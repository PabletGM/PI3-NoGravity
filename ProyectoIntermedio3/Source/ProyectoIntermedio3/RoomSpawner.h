// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"

#include "RoomSpawner.generated.h"

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
	TSubclassOf<AActor> BP_Spawnable;

	UPROPERTY(EditAnywhere)
	float ForwardSpawnOffset = 0;

	UFUNCTION()
	void OnBeginBoxOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void SpawnRoom();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
