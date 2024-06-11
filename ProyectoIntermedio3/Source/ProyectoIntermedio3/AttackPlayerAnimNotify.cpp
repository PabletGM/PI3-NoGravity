// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackPlayerAnimNotify.h"

#include "ProyectoIntermedio3Character.h"

void UAttackPlayerAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		AProyectoIntermedio3Character* Character = Cast<AProyectoIntermedio3Character>(MeshComp->GetOwner());
		if (Character)
		{
			Character->PerformAttackNotifyAnim();
		}
	}
}
