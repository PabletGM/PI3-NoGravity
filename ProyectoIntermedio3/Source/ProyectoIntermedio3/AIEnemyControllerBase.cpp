// Fill out your copyright notice in the Description page of Project Settings.


#include "AIEnemyControllerBase.h"

#include "AIEnemyCharacterBase.h"
#include "BrainComponent.h"
#include "ProyectoIntermedio3Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Logging/StructuredLog.h"


void AAIEnemyControllerBase::BeginPlay()
{
	Super::BeginPlay();	
}

void AAIEnemyControllerBase::CheckTarget()
{
	// Checks AI Type and add to the
	UBlackboardComponent* BlackboardComponent = BrainComponent->GetBlackboardComponent();

	auto* target = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	// Checks for the Target
	if(target && !Cast<AProyectoIntermedio3Character>(target)->isDead)
		BlackboardComponent->SetValueAsObject("Target", target->GetOwner());
	else
		BlackboardComponent->SetValueAsObject("Target", NULL);

	CheckAIType();
}

void AAIEnemyControllerBase::CheckAIType()
{
	// Checks AI Type and add to the
	UBlackboardComponent* BlackboardComponent = BrainComponent->GetBlackboardComponent();

	// Sets type of AI
	APawn* AIPawn = GetPawn();

	if(AIPawn)
		BlackboardComponent->SetValueAsEnum("AI_Type", Cast<AAIEnemyCharacterBase>(AIPawn)->AIType - 1);
}

void AAIEnemyControllerBase::CheckTargetDistance()
{
	UBlackboardComponent* BlackboardComponent = BrainComponent->GetBlackboardComponent();

	APawn* AIPawn = GetPawn();

	APlayerController* PlayerController = Cast<APlayerController>(BlackboardComponent->GetValueAsObject("Target"));

	//float Distance = AIPawn->GetDistanceTo(PlayerCharacter->GetOwner());

	float Distance = (AIPawn->GetActorLocation() - PlayerController->GetPawn()->GetActorLocation()).Length();

	UE_LOGFMT(LogTemp, Log, "Distance {0}", Distance);

	if (Distance <= 300.0f)
		BlackboardComponent->SetValueAsBool("Chase", true);
	else
		BlackboardComponent->SetValueAsBool("Chase", false);
}

EPathFollowingRequestResult::Type AAIEnemyControllerBase::MoveToTarget()
{
	UBlackboardComponent* BlackboardComponent = BrainComponent->GetBlackboardComponent();

	APlayerController* PlayerController = Cast<APlayerController>(BlackboardComponent->GetValueAsObject("Target"));

	EPathFollowingRequestResult::Type MoveToTargetResult = MoveToActor(PlayerController);

	return MoveToTargetResult;
}

void AAIEnemyControllerBase::MoveRandom()
{
	//UE_LOGFMT(LogTemp, Log, "Moving Randomly");

	APawn* AIPawn = GetPawn();
	FVector2D perlinInitialLocation = {AIPawn->GetActorLocation().X, AIPawn->GetActorLocation().Y};

	AIPawn->SetActorLocation(AIPawn->GetActorLocation() + FMath::PerlinNoise2D(perlinInitialLocation) * 100);

}

void AAIEnemyControllerBase::AttackTarget()
{
	UBlackboardComponent* BlackboardComponent = BrainComponent->GetBlackboardComponent();

	APlayerController* PlayerController = Cast<APlayerController>(BlackboardComponent->GetValueAsObject("Target"));

	if(!PlayerController)
	{
		UE_LOGFMT(LogTemp, Log, "Failed controller");
		return;
	}

	auto *player = Cast<AProyectoIntermedio3Character>(PlayerController->GetCharacter());

	if(!player)
	{
		UE_LOGFMT(LogTemp, Log, "Failed player");
		return;
	}
	
	player->TakeDamageFromAI(AIDamage);
}
