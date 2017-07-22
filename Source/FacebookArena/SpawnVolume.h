// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

UCLASS()
class FACEBOOKARENA_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

	virtual void Spawn(const FString PictureURL);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Spawn box volume */
	UPROPERTY(EditDefaultsOnly, Category = EnemySpawner)
	class UBoxComponent* WhereToSpawn;

	// /** The enemy to spawn */
	UPROPERTY(EditAnywhere, Category = EnemySpawner)
	TSubclassOf<class AAvatarPaperSpriteActor> BP_AvatarPaperSpriteActor;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FVector GetRandomPointInVolume();

	/** reference to game mode */
	class AGameMode_FA* GameMode_FA;

	
};
