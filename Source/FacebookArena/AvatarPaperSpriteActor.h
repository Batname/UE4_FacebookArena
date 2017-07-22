// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "AvatarPaperSpriteActor.generated.h"

/**
 * 
 */
UCLASS()
class FACEBOOKARENA_API AAvatarPaperSpriteActor : public APaperSpriteActor
{
	GENERATED_BODY()

public:
	AAvatarPaperSpriteActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
/** Referense to root sprite comp[onent */
class UPaperSpriteComponent* PaperSpriteComp;

public:
	FHttpModule* Http;
	
	/* The actual HTTP call */
	UFUNCTION()
	void GetAvatarHttpCall(const FString PictureURL);
	
	/*Assign this function to call when the GET request processes sucessfully*/
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	
};
