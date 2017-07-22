// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode_FA.h"

#include "FacebookArenaCharacter.h"
#include "PlayerController_FA.h"
#include "HUD_FA.h"
#include "SpawnVolume.h"

#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

AGameMode_FA::AGameMode_FA()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<AFacebookArenaCharacter> PlayerPawnBPClass(TEXT("/Game/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// Set player controller
	static ConstructorHelpers::FClassFinder<APlayerController_FA> BP_PlayerController_FA(TEXT("/Game/Blueprints/BP_PlayerController_FA"));
	if (BP_PlayerController_FA.Class != NULL)
	{
		PlayerControllerClass = BP_PlayerController_FA.Class;
	}

	// Set HUD
	static ConstructorHelpers::FClassFinder<AHUD_FA> BP_HUD_FA(TEXT("/Game/Blueprints/BP_HUD_FA"));
	if (BP_HUD_FA.Class != NULL)
	{
		HUDClass = BP_HUD_FA.Class;
	}
}


void AGameMode_FA::BeginPlay()
{
	Super::BeginPlay();

	// Set reference to spawner
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundActors);
	for (auto Actor : FoundActors)
	{
		SpawnVolume = Cast<ASpawnVolume>(Actor);
	}
}

void AGameMode_FA::SpawnAll()
{
	for (auto PictureURL : FriendsPictures)
	{
		SpawnVolume->Spawn(PictureURL);
	}
}