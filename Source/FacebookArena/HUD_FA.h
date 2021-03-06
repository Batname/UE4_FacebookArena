// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUD_FA.generated.h"

/**
 * 
 */
UCLASS()
class FACEBOOKARENA_API AHUD_FA : public AHUD
{
	GENERATED_BODY()
	
public:
	AHUD_FA();

protected:
	virtual void BeginPlay() override;
	virtual void DrawHUD() override;
};
