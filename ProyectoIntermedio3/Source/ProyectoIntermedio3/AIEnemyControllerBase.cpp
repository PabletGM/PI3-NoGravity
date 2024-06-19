// Fill out your copyright notice in the Description page of Project Settings.


#include "AIEnemyControllerBase.h"

#include "BrainComponent.h"
#include "Proyecto3PlayerController.h"
#include "ProyectoIntermedio3Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Logging/StructuredLog.h"

void AAIEnemyControllerBase::CheckTarget()
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

	auto* controller= Cast<AProyecto3PlayerController>(BlackboardComponent->GetValueAsObject("Target"));

	if(!controller)
	{
		UE_LOGFMT(LogTemp, Log, "Failed controller");
		return;
	}

	auto *player = Cast<AProyectoIntermedio3Character>(controller->GetCharacter());

	if(!player)
	{
		UE_LOGFMT(LogTemp, Log, "Failed player");
		return;
	}
	
	player->TakeDamageFromAI(AIDamage);
}
