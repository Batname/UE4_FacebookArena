// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ArenaActorInterface.generated.h"

/**
 * 
 */
//UCLASS()
//class FACEBOOKARENA_API UArenaActorInterface : public UObject
//{
//	GENERATED_BODY()
//	
//	
//	
//	
//};


UINTERFACE(Blueprintable)
class UArenaActorInterface : public UInterface
{
	GENERATED_BODY()
};


class IArenaActorInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(Category = "ArenaActorInterface")
	virtual void AffectHealth(float Delta);
};