// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComponent.h"

#include "AIEnemyCharacterBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ProyectoIntermedio3Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UAttackComponent::UAttackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//reference to world
	World = GetWorld();
}


// Called when the game starts
void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UAttackComponent::PerformRaycast()
{
	//gets a reference of player
	APlayerController* PlayerController = Cast<APlayerController>(GetOwner()->GetInstigatorController());

	//gets a reference of Player proyecto
	auto* player = Cast<AProyectoIntermedio3Character>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());

	//see if it exists
	if (!PlayerController) return;

	// Obtain the position and rotation of the player
	FVector PlayerLocation = player->GetActorLocation();
	FRotator PlayerRotation = player->GetActorRotation();

	// obtain the forward direction
	FVector ForwardDirection = player->GetActorForwardVector();

	// calculate the end of the sphere trace depending on the forwardDirection
	FVector SphereTraceEnd = PlayerLocation + ForwardDirection * 200.f;

	//create hitResult
	FHitResult HitResult;

	//creates the variable
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(player);

	// Define the type of collision that is pawn
	ECollisionChannel TraceChannel = ECC_Pawn;

	// Convert to a valid argument of the SphereTraceSingle
	ETraceTypeQuery TraceTypeQuery1 = UEngineTypes::ConvertToTraceType(TraceChannel);

	// Set the radius for the sphere trace
	float SphereRadius = 50.f;

	//Make parameters of collision
	bool bHit = UKismetSystemLibrary::SphereTraceSingle(
		GetWorld(), 
		PlayerLocation, 
		SphereTraceEnd, 
		SphereRadius, 
		TraceTypeQuery1, 
		true, 
		{ player }, 
		EDrawDebugTrace::ForDuration, 
		HitResult, 
		true
	);

	//if sphere trace hit
	if (bHit)
	{
		//the actor that has hit the sphere trace
		AActor* HitActor = HitResult.GetActor();

		//detect enemyInterface IDamageable
		IDamageable* damageable = Cast<IDamageable>(HitResult.GetActor());

		//if it exists
		if(damageable)
		{
			// Cast to AAIEnemyCharacterBase
			AAIEnemyCharacterBase* EnemyCharacter = Cast<AAIEnemyCharacterBase>(HitResult.GetActor());
			if (EnemyCharacter)
			{
				// Call the method on AAIEnemyCharacterBase
				EnemyCharacter->TakeDamage(damageToEnemyAttackPlayer);
			}
			//kill the enemy
			UE_LOG(LogTemp, Warning, TEXT("Kill the Enemy!"));
			
			// TODO Must
			//	TakeDamage(float damageAmmount)
			// from AIEnemyCharacterBase
			// TODO well it should have an override function from the damageable interface
		}
		else
		{
			//enemy not found
			UE_LOG(LogTemp, Warning, TEXT("Enemy not found!"));
		}
	}
}

