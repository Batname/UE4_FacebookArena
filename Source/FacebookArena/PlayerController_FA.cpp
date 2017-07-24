// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController_FA.h"
#include "StartMenuWidget.h"
#include "GameSettingsWidget.h"
#include "GameMode_FA.h"
#include "FB_AccountData.h"

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


void APlayerController_FA::GetHttpCall(const FString& FacebookID, const FString& URL, HttpRequestCallback Callback)
{
	FString API_Path = GameMode_FA->GetFB_ApiPath() + FacebookID + URL + GameMode_FA->GetFB_Token();

	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, Callback);
	Request->SetURL(API_Path);
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->SetHeader("FacebookID", FacebookID);
	Request->ProcessRequest();
}


void APlayerController_FA::GetFriendsHttpCall(const FString& FacebookID)
{	
	GameMode_FA->PlayerFacebookID = FacebookID;
	GetHttpCall(FacebookID, FString("/friends?access_token="), &APlayerController_FA::OnGetFriendsResponseReceived);
}

void APlayerController_FA::GetEnemiesHttpCall(const FString& FacebookID)
{
	GameMode_FA->EnemyFacebookID = FacebookID;
	GetHttpCall(FacebookID, FString("/friends?access_token="), &APlayerController_FA::OnGeEnemiesResponseReceived);
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
			GetHttpCall(FriendID, FString("/picture?width=600&height=800&access_token="), &APlayerController_FA::OnGetPictureResponseReceived);
		}
	}
}

void APlayerController_FA::OnGeEnemiesResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("OnGeEnemiesResponseReceived"));
}

// TODO - check response errors
void APlayerController_FA::OnGetPictureResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	// Add to friends array
	FFB_AccountData FB_AccountData;
	FB_AccountData.Id = Request->GetHeader("FacebookID");
	FB_AccountData.OwnerId = GameMode_FA->PlayerFacebookID;
	FB_AccountData.ImagePath = Response->GetHeader("Location");
	FB_AccountData.Type = EAccountType::Friend;
	GameMode_FA->GetFriendsData().Add(FB_AccountData);

	FriendsNumCount++;
	if (FriendsNum == FriendsNumCount)
	{
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

	// Spawn all
	GameMode_FA->SpawnAll();
}

// 100007953361890