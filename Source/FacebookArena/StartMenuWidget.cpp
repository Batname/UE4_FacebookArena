// Fill out your copyright notice in the Description page of Project Settings.


#include "StartMenuWidget.h"

#include "GameMode_FA.h"
#include "PlayerController_FA.h"

void UStartMenuWidget::OpenGameSettingsWidget()
{
	GameMode_FA = Cast<AGameMode_FA>(GetWorld()->GetAuthGameMode());
	GameMode_FA->PlayerController_FA->OpenGameSettingsWidget();
}
