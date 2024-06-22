// Fill out your copyright notice in the Description page of Project Settings.


#include "AIEnemyCharacterBase.h"

#include "AB_EnemyDeepShark.h"
#include "AB_EnemyPiranha.h"
#include "ProyectoIntermedio3Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Logging/StructuredLog.h"

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
		IsAlive = false;
}

void AAIEnemyCharacterBase::Death()
{	
	MakeSoundEffect("enemyDeathSound");

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if(AnimInstance && DeathMontage && !isAlreadyDeath)
	{
		isAlreadyDeath = true;
		AnimInstance->Montage_Play(DeathMontage);

		//Cast to the specific anim instance class and set the bIsDead variable
		if (UAB_EnemyDeepShark* ABInstanceDeepShark = Cast<UAB_EnemyDeepShark>(AnimInstance))
			ABInstanceDeepShark->Death();  // Set this to true to prevent idle animation

		//Cast to the specific anim instance class and set the bIsDead variable
		if (UAB_EnemyPiranha* ABInstancePiranha = Cast<UAB_EnemyPiranha>(AnimInstance))
			ABInstancePiranha->Death();  // Set this to true to prevent idle animation
	}
}

void AAIEnemyCharacterBase::PerformDeathNotifyAnim()
{
	UE_LOGFMT(LogTemp, Log, "Enemy Dies");
	if(BP_Pearl)
	{
		UWorld* world = GetWorld();
		if (!world)
			return;

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		world->SpawnActor<APearl>(BP_Pearl, GetActorLocation(), GetActorRotation(), SpawnParams);
	}

	//this->Destroy();
}

// Called when the game starts or when spawned
void AAIEnemyCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	GetCharacterMovement()->MaxWalkSpeed = Speed;

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
