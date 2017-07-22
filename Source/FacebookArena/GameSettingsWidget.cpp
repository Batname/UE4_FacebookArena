// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSettingsWidget.h"

#include "GameMode_FA.h"
#include "PlayerController_FA.h"


void UGameSettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameMode_FA = AGameMode_FA::StaticClass()->GetDefaultObject<AGameMode_FA>();
}



