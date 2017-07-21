// Fill out your copyright notice in the Description page of Project Settings.


#include "AvatarPaperSpriteActor.h"
#include "FB_AccountData.h"

#include "PaperSpriteComponent.h"
#include "Engine/Texture2D.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Interfaces/IImageWrapper.h"
#include "Interfaces/IImageWrapperModule.h"

#include "Engine/DataTable.h"
#include "UObject/ConstructorHelpers.h"

AAvatarPaperSpriteActor::AAvatarPaperSpriteActor()
{
	// Set referense to root sprite comp
	PaperSpriteComp = GetRenderComponent();

	//When the object is constructed, Get the HTTP module
	Http = &FHttpModule::Get();

	// TODO - data table for test
	static ConstructorHelpers::FObjectFinder<UDataTable>AvatarsObj(TEXT("DataTable'/Game/Data/Avatars.Avatars'"));
	AvatarsDataTable = AvatarsObj.Object;
}

void AAvatarPaperSpriteActor::BeginPlay()
{
	Super::BeginPlay();

	GetAvatarHttpCall();
}


void AAvatarPaperSpriteActor::GetAvatarHttpCall()
{
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &AAvatarPaperSpriteActor::OnResponseReceived);

	// TODO - test data table
	TArray<FName> RowNames = AvatarsDataTable->GetRowNames();
	FString ContextString;
	FFB_AccountData* FB_AccountData = AvatarsDataTable->FindRow<FFB_AccountData>(RowNames[0], ContextString);

	// URL params
	Request->SetURL(FB_AccountData->ImagePath);
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("image/jpeg"));
	Request->ProcessRequest();
}


// https://answers.unrealengine.com/questions/75929/is-it-possible-to-load-bitmap-or-jpg-files-at-runt.html
void AAvatarPaperSpriteActor::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	TArray<uint8> ImageDataArray = Response->GetContent();
	UTexture2D* MyTex;

	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	IImageWrapperPtr ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::JPEG);

	if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(ImageDataArray.GetData(), ImageDataArray.Num()))
	{
		const TArray<uint8>* UncompressedBGRA = NULL;
		if (ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedBGRA))
		{
			MyTex = UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_B8G8R8A8);

			void* TextureData = MyTex->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
			FMemory::Memcpy(TextureData, UncompressedBGRA->GetData(), UncompressedBGRA->Num());
			MyTex->PlatformData->Mips[0].BulkData.Unlock();

			MyTex->UpdateResource();
		}
	}


	// Setup texture dynamicly
	UMaterialInstanceDynamic* DynamicMatInstance = PaperSpriteComp->CreateAndSetMaterialInstanceDynamic(0);
	if (DynamicMatInstance)
	{
		DynamicMatInstance->SetTextureParameterValue(FName("TextureMap"), MyTex);
	}
}


