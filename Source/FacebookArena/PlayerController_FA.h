// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "PlayerController_FA.generated.h"

/**
 * 
 */
UCLASS()
class FACEBOOKARENA_API APlayerController_FA : public APlayerController
{
	GENERATED_BODY()
	
public:
	APlayerController_FA();

	/** Open second widget after start up widget */
	void OpenGameSettingsWidget();

	/** Handle after click start game */
	UFUNCTION()
	void StartGame();

	/* The get friends HTTP call */
	UFUNCTION()
	void GetPictureHttpCall(const FString& FacebookID);


	/* The get friends HTTP call */
	UFUNCTION()
	void GetFriendsHttpCall(const FString& FacebookID);

protected:
	virtual void BeginPlay() override;
 
	/** StartMenuWidget blueprint reference */
	UPROPERTY(EditDefaultsOnly, Category = Widgets)
	TSubclassOf<class UStartMenuWidget> BP_StartMenuWidget;

	/** GameSettingsWidget blueprint reference */
	UPROPERTY(EditDefaultsOnly, Category = Widgets)
	TSubclassOf<class UGameSettingsWidget> BP_GameSettingsWidget;
	
private:
	/** Reference to StartMenuWidget cpp class */
	class UStartMenuWidget* StartMenuWidget;

	/** Reference to GameSettingsWidget cpp class */
	class UGameSettingsWidget* GameSettingsWidget;

	/** Set reference to game mode */
	class AGameMode_FA* GameMode_FA;

	FHttpModule* Http;

	/*Assign this function to call when the GET request processes sucessfully*/
	void OnGetFriendsResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	void OnGetPictureResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	uint32 FriendsNum = 0;
	uint32 FriendsNumCount = 0;
};
