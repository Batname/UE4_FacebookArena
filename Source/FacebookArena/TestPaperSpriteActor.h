// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
#include "Runtime/Online/HTTP/Public/Http.h"
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

// ----- HTTP call
// -----------------
public:
	FHttpModule* Http;
	
	/* The actual HTTP call */
	UFUNCTION()
	void MyHttpCall();
	
	/*Assign this function to call when the GET request processes sucessfully*/
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
