// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController_FA.h"
#include "StartMenuWidget.h"
#include "GameSettingsWidget.h"
#include "GameMode_FA.h"

#include "UObject/ConstructorHelpers.h"

APlayerController_FA::APlayerController_FA()
{
	// Setup widgets
	static ConstructorHelpers::FClassFinder<UStartMenuWidget> BP_StartMenuWidgetRef(TEXT("/Game/Blueprints/UI/BP_StartMenuWidget"));
	BP_StartMenuWidget = BP_StartMenuWidgetRef.Class;

	static ConstructorHelpers::FClassFinder<UGameSettingsWidget> BP_GameSettingsWidgetRef(TEXT("/Game/Blueprints/UI/BP_GameSettingsWidget"));
	BP_GameSettingsWidget = BP_GameSettingsWidgetRef.Class;
}

void APlayerController_FA::BeginPlay()
{
	Super::BeginPlay();

	// setup reference to Game mode
	GameMode_FA = AGameMode_FA::StaticClass()->GetDefaultObject<AGameMode_FA>();
	GameMode_FA->PlayerController_FA = this;

	// Show cursor by default
	bShowMouseCursor = true;

	// Create widgets
	StartMenuWidget = CreateWidget<UStartMenuWidget>(this, BP_StartMenuWidget);
	GameSettingsWidget = CreateWidget<UGameSettingsWidget>(this, BP_GameSettingsWidget);

	// Setup main menu widget
	StartMenuWidget->AddToViewport();
}

void APlayerController_FA::OpenGameSettingsWidget()
{
	StartMenuWidget->RemoveFromViewport();
	GameSettingsWidget->AddToViewport();
}