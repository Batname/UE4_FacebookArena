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
private:
	/** Set reference to game mode */
	class AGameMode_FA* GameMode_FA;
	
	
};
