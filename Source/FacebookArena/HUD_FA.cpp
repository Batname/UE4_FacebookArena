// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD_FA.h"
#include "StartMenuWidget.h"
#include "PlayerController_FA.h"

AHUD_FA::AHUD_FA()
{

}

void AHUD_FA::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));

	// Set reference to controller
	PlayerController = Cast<APlayerController_FA>(GetOwningPlayerController());

	// Add BP_StartMenuWidget to viewport
	if (BP_StartMenuWidget != nullptr)
	{
		// Create and add to view port
		StartMenuWidget = CreateWidget<UStartMenuWidget>(PlayerController, BP_StartMenuWidget);
		StartMenuWidget->AddToViewport();
	}

}
void AHUD_FA::DrawHUD()
{
	Super::DrawHUD();
}
