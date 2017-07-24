// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController_FA.h"
#include "StartMenuWidget.h"
#include "GameSettingsWidget.h"
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
	GetHttpCall(FacebookID, FString("/friends?access_token="), &APlayerController_FA::OnGetPlayerFriendsResponseReceived);

	// Get player image call
	FriendsNum++;
	GetHttpCall(GameMode_FA->PlayerFacebookID, FString("/picture?width=600&height=800&access_token="), &APlayerController_FA::OnGetFriendsPictureResponseReceived);
}

void APlayerController_FA::GetEnemiesHttpCall(const FString& FacebookID)
{
	GameMode_FA->EnemyFacebookID = FacebookID;
	GetHttpCall(FacebookID, FString("/friends?access_token="), &APlayerController_FA::OnGetEnemyFriendsResponseReceived);

	// Get enemy image call
	EnemiesNum++;
	GetHttpCall(GameMode_FA->EnemyFacebookID, FString("/picture?width=600&height=800&access_token="), &APlayerController_FA::OnGetEnemiesPictureResponseReceived);
}

void APlayerController_FA::ParseFriendsResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, uint32& UserCount, HttpRequestCallback Callback)
{
	// Get player friends calls
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

	//Deserialize the json data given Reader and the actual object to deserialize
	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		//Get the value of the json object by field name
		TArray <TSharedPtr<FJsonValue>> DataArray = JsonObject->GetArrayField("data");

		UserCount += DataArray.Num();

		for (int i = 0; i != DataArray.Num(); i++)
		{
			TSharedPtr<FJsonObject> Friend = DataArray[i]->AsObject();
			FString UserID = Friend->GetStringField("id");
			GetHttpCall(UserID, FString("/picture?width=600&height=800&access_token="), Callback);
		}
	}
}

// TODO - check response errors
void APlayerController_FA::OnGetPlayerFriendsResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	ParseFriendsResponseReceived(Request, Response, bWasSuccessful, FriendsNum, &APlayerController_FA::OnGetFriendsPictureResponseReceived);
}

void APlayerController_FA::OnGetEnemyFriendsResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	ParseFriendsResponseReceived(Request, Response, bWasSuccessful, EnemiesNum, &APlayerController_FA::OnGetEnemiesPictureResponseReceived);
}

// TODO - check response errors
void APlayerController_FA::ParsePictureResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, uint32 UserNum, uint32 & UserNumCount, TArray<FFB_AccountData>& DataArray, const FString& OwnerId)
{
	// Add to friends array
	FFB_AccountData FB_AccountData;
	FB_AccountData.Id = Request->GetHeader("FacebookID");
	FB_AccountData.OwnerId = OwnerId;
	FB_AccountData.ImagePath = Response->GetHeader("Location");
	DataArray.Add(FB_AccountData);

	UserNumCount++;
	if (UserNum == FriendsNumCount)
	{
		// Disable input
		GameSettingsWidget->ConnectFacebookID_Done();
	}

	if (UserNum == EnemiesNumCount)
	{
		// Disable input
		GameSettingsWidget->ConnectEnemyFacebookID_Done();
	}

	if (FriendsNumCount && FriendsNum == FriendsNumCount && EnemiesNumCount && EnemiesNum == EnemiesNumCount)
	{
		// TODO - add opponent pictures
		// Show start game button
		GameSettingsWidget->ShowStartButton();
	}
}

void APlayerController_FA::OnGetFriendsPictureResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	ParsePictureResponseReceived(Request, Response, bWasSuccessful, FriendsNum, FriendsNumCount, GameMode_FA->GetFriendsData(), GameMode_FA->PlayerFacebookID);
}

void APlayerController_FA::OnGetEnemiesPictureResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	ParsePictureResponseReceived(Request, Response, bWasSuccessful, EnemiesNum, EnemiesNumCount, GameMode_FA->GetEnemiesData(), GameMode_FA->EnemyFacebookID);
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