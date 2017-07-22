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
	
protected:
	virtual void BeginPlay() override;

	/** StartMenuWidget blueprint reference */
	UPROPERTY(EditDefaultsOnly, Category = Widgets)
	TSubclassOf<class UStartMenuWidget> BP_StartMenuWidget;
	
private:
	/** Reference to StartMenuWidget cpp class */
	class UStartMenuWidget* StartMenuWidget;
};
