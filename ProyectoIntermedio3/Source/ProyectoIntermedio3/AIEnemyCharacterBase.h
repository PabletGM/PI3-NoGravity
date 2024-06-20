// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Damageable.h"
#include "GameFramework/Character.h"

#include "AIEnemyCharacterBase.generated.h"

UCLASS()
class PROYECTOINTERMEDIO3_API AAIEnemyCharacterBase : public ACharacter, public IDamageable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIEnemyCharacterBase();

	void TakeDamage(float damageAmmount);
	void Death();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditDefaultsOnly) float MaxHealth;
	UPROPERTY() float CurrentHealth;
	UPROPERTY(EditDefaultsOnly) UEnum* AIType = nullptr;
};
