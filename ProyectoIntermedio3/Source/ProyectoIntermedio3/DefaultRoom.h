// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoomSpawner.h"

#include "DefaultRoom.generated.h"

UCLASS()
class PROYECTOINTERMEDIO3_API ADefaultRoom : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* RootCmp = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* NextRoomCollision = nullptr;
	
public:	
	// Sets default values for this actor's properties
	ADefaultRoom();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
