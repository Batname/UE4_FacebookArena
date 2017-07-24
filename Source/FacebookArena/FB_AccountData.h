// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "FB_AccountData.generated.h"

UENUM(BlueprintType)
enum class EAccountType : uint8
{
	PlayerCharacter UMETA(DisplayName = "PlayerCharacter"),
	EnemyCharacter UMETA(DisplayName = "EnemyCharacter"),
	Enemy	UMETA(DisplayName = "Enemy"),
	Friend	UMETA(DisplayName = "Friend")
};

USTRUCT(BlueprintType)
struct FFB_AccountData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	/*The subtitle that will be displayed for a specific period of time in our UI*/
	UPROPERTY(EditAnywhere)
	FString Id;

	/* Keep in track owner */
	UPROPERTY(EditAnywhere)
	FString OwnerId;

	/*The relative time in seconds, that the subtitle will appear*/
	UPROPERTY(EditAnywhere)
	FString ImagePath;

	/*The relative time in seconds, that the subtitle will appear*/
	UPROPERTY(EditAnywhere)
	EAccountType Type;
};
