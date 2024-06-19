// Fill out your copyright notice in the Description page of Project Settings.


#include "AB_GameDiver.h"

UAB_GameDiver::UAB_GameDiver()
{
	bIsDead = false;
}

void UAB_GameDiver::Death()
{
	bIsDead = true;
}
