// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "TestCharacter.generated.h"

UCLASS()
class FACEBOOKARENA_API ATestCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATestCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

// ----- HTTP call
// -----------------
public:
	FHttpModule* Http;
	
	/* The actual HTTP call */
	UFUNCTION()
	void MyHttpCall();
	
	/*Assign this function to call when the GET request processes sucessfully*/
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	
// ---- Test dynamic material
//--------------------------

	/*The static mesh of the actor*/
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* StaticMesh;


	class UTexture2D* TestTex;
};
