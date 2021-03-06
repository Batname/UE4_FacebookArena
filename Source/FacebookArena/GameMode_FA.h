// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "FB_AccountData.h"
#include "GameMode_FA.generated.h"

/**
 * 
 */
UCLASS()
class FACEBOOKARENA_API AGameMode_FA : public AGameMode
{
	GENERATED_BODY()
	
public:
	AGameMode_FA();

	FString& GetFB_Token() { return FB_Token; }
	FString& GetFB_ApiPath() { return FB_ApiPath; }
	TArray<FFB_AccountData>& GetFriendsData() { return FriendsData; }
	TArray<FFB_AccountData>& GetEnemiesData() { return EnemiesData; }


	void SpawnAll();

protected:
	virtual void BeginPlay() override;

	/** Facebook token */
	UPROPERTY(EditDefaultsOnly)
	FString FB_Token;

	/** Facebook token */
	UPROPERTY(EditDefaultsOnly)
	FString FB_ApiPath;
	
public:
	// References to game mode classes
	class AFacebookArenaCharacter* Character_FA;
	class APlayerController_FA* PlayerController_FA;
	class AHUD_FA* HUD_FA;

	FString PlayerFacebookID;
	FString EnemyFacebookID;


private:
	TArray<FFB_AccountData> FriendsData;
	TArray<FFB_AccountData> EnemiesData;
	class ASpawnVolume* FriendsVolume;
	class ASpawnVolume* EnemiesVolume;

};
