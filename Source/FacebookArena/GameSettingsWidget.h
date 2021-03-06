// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameSettingsWidget.generated.h"

/**
 * 
 */
UCLASS()
class FACEBOOKARENA_API UGameSettingsWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;


	UPROPERTY(BlueprintReadWrite)
	FString PlayerFacebookID;

	UPROPERTY(BlueprintReadWrite)
	FString OponentFacebookID;

	UFUNCTION(BlueprintCallable, Category = GameSettingsWidget)
	void ConnectFacebookID();

	UFUNCTION(BlueprintCallable, Category = GameSettingsWidget)
	void ConnectEnemyFacebookID();

	UFUNCTION(BlueprintCallable, Category = GameSettingsWidget)
	void ClickStartButton();


private:
	/** Set reference to game mode */
	class AGameMode_FA* GameMode_FA;

public:
	UFUNCTION(BlueprintImplementableEvent, Category = GameSettingsWidget)
	void ConnectFacebookID_Done();

	UFUNCTION(BlueprintImplementableEvent, Category = GameSettingsWidget)
	void ConnectEnemyFacebookID_Done();

	UFUNCTION(BlueprintImplementableEvent, Category = GameSettingsWidget)
	void ShowStartButton();
};
