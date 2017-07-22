// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode_FA.h"
#include "FacebookArenaCharacter.h"
#include "UObject/ConstructorHelpers.h"


AGameMode_FA::AGameMode_FA()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}


