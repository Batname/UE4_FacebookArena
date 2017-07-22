// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolume.h"
#include "AvatarPaperSpriteActor.h"
#include "GameMode_FA.h"
#include "FacebookArenaCharacter.h"


#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create root box component
	WhereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn"));
	RootComponent = WhereToSpawn;
	WhereToSpawn->SetCollisionProfileName(FName("OverlapAll"));
	WhereToSpawn->SetSimulatePhysics(false);
	WhereToSpawn->bGenerateOverlapEvents = true;

}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();

	// Set reference to game mode
	GameMode_FA = Cast<AGameMode_FA>(GetWorld()->GetAuthGameMode());
}

// TODO rewrite for friends and opponents
void ASpawnVolume::Spawn(const FString PictureURL)
{
	FVector SpawnLocation = GetRandomPointInVolume();
	FVector CharacterLocation = GameMode_FA->Character_FA->GetActorLocation();

	// Rotate to character
	FRotator SpawnRotation;
	SpawnRotation.Yaw = (CharacterLocation - SpawnLocation).Rotation().Yaw;
	SpawnRotation.Pitch = 0.f;
	SpawnRotation.Roll = 0.f;

	// Spawn parameters
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	// Spawn
	if (BP_AvatarPaperSpriteActor != nullptr)
	{
		// TODO - store in array in future
		AAvatarPaperSpriteActor* AvatarPaperSpriteActor = GetWorld()->SpawnActor<AAvatarPaperSpriteActor>(BP_AvatarPaperSpriteActor, SpawnLocation, SpawnRotation, SpawnParams);
		AvatarPaperSpriteActor->GetAvatarHttpCall(PictureURL);
	}
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ASpawnVolume::GetRandomPointInVolume()
{
	FVector SpawnOrigin = WhereToSpawn->Bounds.Origin;
	FVector SpawnExtend = WhereToSpawn->Bounds.BoxExtent;

	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtend);
}