// Fill out your copyright notice in the Description page of Project Settings.


#include "AB_EnemyDeepShark.h"

UAB_EnemyDeepShark::UAB_EnemyDeepShark()
{
	bIsDead = false;
}

void UAB_EnemyDeepShark::Death()
{
	bIsDead = true;
}
