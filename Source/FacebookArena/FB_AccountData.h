// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "FB_AccountData.generated.h"

/**
 * 
 */
// UCLASS()
// class FACEBOOKARENA_API UFB_AccountData : public UObject
// {
// 	GENERATED_BODY()
	
	
	
	
// };


USTRUCT(BlueprintType)
struct FFB_AccountData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	/*The subtitle that will be displayed for a specific period of time in our UI*/
	UPROPERTY(EditAnywhere)
	int Id;

	/*The relative time in seconds, that the subtitle will appear*/
	UPROPERTY(EditAnywhere)
	FString ImagePath;
};
