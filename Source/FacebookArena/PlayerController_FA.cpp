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
	GameMode_FA = Cast<AGameMode_FA>(GetWorld()->GetAuthGameMode());
	GameMode_FA->PlayerController_FA = this;

	// Setup HTTP module
	Http = &FHttpModule::Get();

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

void APlayerController_FA::GetFriendsHttpCall(const FString& FacebookID)
{
	FString API_Path = GameMode_FA->GetFB_ApiPath() + FacebookID + FString("/friends?access_token=") + GameMode_FA->GetFB_Token();

	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &APlayerController_FA::OnGetFriendsResponseReceived);
	Request->SetURL(API_Path);
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();
}

// TODO - check response errors
void APlayerController_FA::OnGetFriendsResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	//Create a pointer to hold the json serialized data
	TSharedPtr<FJsonObject> JsonObject;
	
	//Create a reader pointer to read the json data
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	
	//Deserialize the json data given Reader and the actual object to deserialize
	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		//Get the value of the json object by field name
		TArray <TSharedPtr<FJsonValue>> FriendsArray = JsonObject->GetArrayField("data");

		FriendsNum = FriendsArray.Num();

		for (int i = 0; i != FriendsArray.Num(); i++)
		{
			TSharedPtr<FJsonObject> Friend = FriendsArray[i]->AsObject();
			FString FriendID = Friend->GetStringField("id");
			GetPictureHttpCall(FriendID);
		}
	}
}

void APlayerController_FA::GetPictureHttpCall(const FString& FacebookID)
{
	FString API_Path = GameMode_FA->GetFB_ApiPath() + FacebookID + FString("/picture?width=600&height=800&access_token=") + GameMode_FA->GetFB_Token();

	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &APlayerController_FA::OnGetPictureResponseReceived);
	Request->SetURL(API_Path);
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();
}

// TODO - check response errors
void APlayerController_FA::OnGetPictureResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	// Add to friends array
	GameMode_FA->GetFriendsPictures().Add(Response->GetHeader("Location"));

	FriendsNumCount++;
	if (FriendsNum == FriendsNumCount)
	{
		UE_LOG(LogTemp, Warning, TEXT("OnGetPictureResponseReceived DONE"));

		// Disable input
		GameSettingsWidget->ConnectFacebookID_Done();

		// TODO - add opponent pictures
		// Show start game button
		GameSettingsWidget->ShowStartButton();
	}
}

void APlayerController_FA::StartGame()
{
	// Hide cursor
	bShowMouseCursor = false;

	// remove option widget
	GameSettingsWidget->RemoveFromViewport();

}

// 100007953361890