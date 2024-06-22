// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Damageable.h"
#include "GameFramework/Character.h"
#include "AudioManager.h"

#include "AIEnemyCharacterBase.generated.h"

UCLASS()
class PROYECTOINTERMEDIO3_API AAIEnemyCharacterBase : public ACharacter, public IDamageable
{
	GENERATED_BODY()

	//Animation montage for attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AttackMontage = nullptr;

	//Animation montage for death
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* DeathMontage = nullptr;

public:
	// Sets default values for this character's properties
	AAIEnemyCharacterBase();

	UFUNCTION() void TakeDamage(float damageAmount);
	UFUNCTION() void Death();
	UFUNCTION() void PerformDeathNotifyAnim();
	UFUNCTION() void DestroyItself();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void PostBeginPlay();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void MakeSoundEffect(FString nameSound);

	UFUNCTION()
	void MakeSoundEffect2(FString nameSound2);

	UFUNCTION()
	void FindAudioManager();

public:
	UPROPERTY(EditAnywhere) bool IsAlive = true;
	UPROPERTY(meta=(BItmask,BitmaskEnum="/Game/_NoGravity/Blueprints/AI/AI_Type.AI_Type"), EditAnywhere) int AIType = 0;
	UPROPERTY(EditAnywhere) float MaxHealth = 0.0f;
	UPROPERTY(EditAnywhere) float CurrentHealth = 0.0f;
	UPROPERTY(EditAnywhere) int32 Damage = 10.0f;
	UPROPERTY(EditAnywhere) float Speed = 100.0f;

private:
	
	bool isAlreadyDeath = false;

	// Reference to the instantiated AudioManager
	UPROPERTY()
	AAudioManager* AudioManagerInstance;

	// Reference to the AudioManager
	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TSubclassOf<AAudioManager> BP_AudioManager;
};
