// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSettingsWidget.h"

#include "GameMode_FA.h"
#include "PlayerController_FA.h"
#include "FacebookArenaCharacter.h"

void UGameSettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	GameMode_FA = Cast<AGameMode_FA>(GetWorld()->GetAuthGameMode());
}

void UGameSettingsWidget::ConnectFacebookID()
{
	GameMode_FA->PlayerController_FA->GetFriendsHttpCall(PlayerFacebookID);
}

void UGameSettingsWidget::ConnectEnemyFacebookID()
{
	GameMode_FA->PlayerController_FA->GetEnemiesHttpCall(OponentFacebookID);
}

void UGameSettingsWidget::ClickStartButton()
{
	GameMode_FA->PlayerController_FA->StartGame();
	GameMode_FA->Character_FA->ToggleInput();
}