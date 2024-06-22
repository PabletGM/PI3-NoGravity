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

	NavSystem = Cast<UNavigationSystemV1>(GetWorld()->GetNavigationSystem());
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

EPathFollowingRequestResult::Type AAIEnemyControllerBase::MoveRandom()
{
	APawn* AIPawn = GetPawn();

	FNavLocation Result;
	NavSystem->GetRandomReachablePointInRadius(AIPawn->GetActorLocation(),20000, Result);

	EPathFollowingRequestResult::Type MoveToRandomResult = MoveToLocation(Result);

	return MoveToRandomResult;
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
