// Fill out your copyright notice in the Description page of Project Settings.


#include "StartMenuWidget.h"

#include "GameMode_FA.h"
#include "PlayerController_FA.h"


void UStartMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameMode_FA = AGameMode_FA::StaticClass()->GetDefaultObject<AGameMode_FA>();
}

void UStartMenuWidget::OpenGameSettingsWidget()
{
	GameMode_FA->PlayerController_FA->OpenGameSettingsWidget();
}
