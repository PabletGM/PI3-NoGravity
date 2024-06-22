// Fill out your copyright notice in the Description page of Project Settings.


#include "AB_EnemyPiranha.h"

UAB_EnemyPiranha::UAB_EnemyPiranha()
{
	bIsDead = false;
}

void UAB_EnemyPiranha::Death()
{
	bIsDead = true;
}
