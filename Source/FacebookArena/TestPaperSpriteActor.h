// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
#include "TestPaperSpriteActor.generated.h"

/**
 * 
 */
UCLASS()
class FACEBOOKARENA_API ATestPaperSpriteActor : public APaperSpriteActor
{
	GENERATED_BODY()
	
	
public:
	ATestPaperSpriteActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	class UPaperSpriteComponent* PaperSpriteComp;
	class UTexture2D* TestTex;
};
