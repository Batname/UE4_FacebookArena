// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "FB_AccountData.generated.h"

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
};
