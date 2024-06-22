// Fill out your copyright notice in the Description page of Project Settings.


#include "AIEnemyBaseAnimNotify.h"

#include "AIEnemyCharacterBase.h"

void UAIEnemyBaseAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		AAIEnemyCharacterBase* EnemyCharacter = Cast<AAIEnemyCharacterBase>(MeshComp->GetOwner());
		if (EnemyCharacter)
		{
			EnemyCharacter->PerformDeathNotifyAnim();
		}
	}
}
