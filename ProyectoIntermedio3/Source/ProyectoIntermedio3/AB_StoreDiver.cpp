// Fill out your copyright notice in the Description page of Project Settings.


#include "AB_StoreDiver.h"

UAB_StoreDiver::UAB_StoreDiver()
{
	//start speed player at 0
	speedPlayer = 0.0f;
}

//update speed player
void UAB_StoreDiver::UpdateSpeedVariable(float NewValue)
{
	speedPlayer = NewValue;
}

