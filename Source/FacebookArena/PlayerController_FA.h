// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMode_FA.h"
#include "GameFramework/PlayerController.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Delegates/DelegateInstanceInterface.h"
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
	void GetFriendsHttpCall(const FString& FacebookID);

	/* The get friends HTTP call */
	UFUNCTION()
	void GetEnemiesHttpCall(const FString& FacebookID);

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

	uint32 FriendsNum = 0;
	uint32 FriendsNumCount = 0;

	uint32 EnemiesNum = 0;
	uint32 EnemiesNumCount = 0;

	typedef void (APlayerController_FA::*HttpRequestCallback)(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void GetHttpCall(const FString& FacebookID, const FString& URL, HttpRequestCallback Callback);

	void ParseFriendsResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, uint32& UserCount, HttpRequestCallback Callback);
	void OnGetPlayerFriendsResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void OnGetEnemyFriendsResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	void ParsePictureResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, uint32 UserNum, uint32& UserNumCount, TArray<FFB_AccountData>& DataArray, const FString& OwnerId);
	void OnGetFriendsPictureResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void OnGetEnemiesPictureResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
