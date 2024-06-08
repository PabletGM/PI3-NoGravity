// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProyectoIntermedio3GameMode.h"
#include "ProyectoIntermedio3Character.h"
#include "UObject/ConstructorHelpers.h"

AProyectoIntermedio3GameMode::AProyectoIntermedio3GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_Proyecto3PlayerController"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}
