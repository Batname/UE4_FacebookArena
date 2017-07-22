// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class FACEBOOKARENA_API UStartMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = MenuWidget)
	void OpenGameSettingsWidget();

private:
	/** Set reference to game mode */
	class AGameMode_FA* GameMode_FA;
};
