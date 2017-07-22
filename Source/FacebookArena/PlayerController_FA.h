// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
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
};
