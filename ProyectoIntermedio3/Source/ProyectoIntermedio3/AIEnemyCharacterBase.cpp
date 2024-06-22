// Fill out your copyright notice in the Description page of Project Settings.


#include "AIEnemyCharacterBase.h"

#include "ProyectoIntermedio3Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAIEnemyCharacterBase::AAIEnemyCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

void AAIEnemyCharacterBase::TakeDamage(float damageAmount)
{
	CurrentHealth -= damageAmount;

	// // //take damage sound IA

	if(damageAmount >= CurrentHealth)
		Death();
}

void AAIEnemyCharacterBase::Death()
{
	// TODO Do whatever it needs to do before die
	IsAlive = false;
	MakeSoundEffect("enemyDeathSound");
	//this->Destroy();
}

// Called when the game starts or when spawned
void AAIEnemyCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;


	GetWorldTimerManager().SetTimerForNextTick(this, &AAIEnemyCharacterBase::PostBeginPlay);
}

void AAIEnemyCharacterBase::PostBeginPlay()
{
	FindAudioManager();
}

// Called every frame
void AAIEnemyCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAIEnemyCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAIEnemyCharacterBase::MakeSoundEffect(FString nameSound)
{
	if (AudioManagerInstance)
	{
		// Example method call on AudioManagerInstance
		// Replace PlaySound with your actual method name and parameters
		USoundBase* Sound = AudioManagerInstance->FindSoundByName(nameSound);
		if (Sound)
		{
			AudioManagerInstance->PlaySoundEffect2(Sound);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Sound not found in AudioManager!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AudioManager instance is null!"));
	}
}

void AAIEnemyCharacterBase::MakeSoundEffect2(FString nameSound2)
{
	if (AudioManagerInstance)
	{
		// Example method call on AudioManagerInstance
		// Replace PlaySound with your actual method name and parameters
		USoundBase* Sound = AudioManagerInstance->FindSoundByName(nameSound2);
		if (Sound)
		{
			AudioManagerInstance->PlaySoundEffect2(Sound);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Sound not found in AudioManager!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AudioManager instance is null!"));
	}
}

void AAIEnemyCharacterBase::FindAudioManager()
{
	//look for AudioManager character
	// Get the player character
	AProyectoIntermedio3Character* PlayerCharacter = Cast<AProyectoIntermedio3Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerCharacter)
	{
		AudioManagerInstance = PlayerCharacter->GetAudioManagerInstance();
	}
}
