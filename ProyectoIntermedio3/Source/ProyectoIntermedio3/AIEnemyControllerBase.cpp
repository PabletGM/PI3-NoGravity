// Fill out your copyright notice in the Description page of Project Settings.


#include "AIEnemyControllerBase.h"

#include "BrainComponent.h"
#include "ProyectoIntermedio3Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

void AAIEnemyControllerBase::CheckTargetDistance()
{

	// Checks AI Type and add to the
	UBlackboardComponent* BlackboardComponent = BrainComponent->GetBlackboardComponent();

	auto* target = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if(target)
		BlackboardComponent->SetValueAsObject("Target", target->GetOwner());
	else
		BlackboardComponent->SetValueAsObject("Target", NULL);
}

EPathFollowingRequestResult::Type AAIEnemyControllerBase::MoveToTarget()
{
	UBlackboardComponent* BlackboardComponent = BrainComponent->GetBlackboardComponent();

	AActor* PlayerCharacter = Cast<AActor>(BlackboardComponent->GetValueAsObject("Target"));

	EPathFollowingRequestResult::Type MoveToTargetResult = MoveToActor(PlayerCharacter);

	return MoveToTargetResult;
}

void AAIEnemyControllerBase::AttackTarget()
{
	UBlackboardComponent* BlackboardComponent = BrainComponent->GetBlackboardComponent();

	AActor* PlayerCharacter = Cast<AActor>(BlackboardComponent->GetValueAsObject("Target"));

	Cast<AProyectoIntermedio3Character>(PlayerCharacter)->TakeDamageFromAI(AIDamage);
}
