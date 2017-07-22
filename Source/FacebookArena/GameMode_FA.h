// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
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

protected:
	virtual void BeginPlay() override;
	
};
