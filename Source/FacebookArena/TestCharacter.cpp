// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCharacter.h"
#include "Interfaces/IImageWrapper.h"
#include "Interfaces/IImageWrapperModule.h"
#include "Engine/Texture2D.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "UObject/ConstructorHelpers.h"

#include "Components/StaticMeshComponent.h"


// Sets default values
ATestCharacter::ATestCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//When the object is constructed, Get the HTTP module
	Http = &FHttpModule::Get();

	//Initialize the static mesh component
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);


	// Texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> TexObj(TEXT("/Game/Textures/MY_UE4_LOGO"));
	TestTex = TexObj.Object;
}

// Called when the game starts or when spawned
void ATestCharacter::BeginPlay()
{
	MyHttpCall();
	Super::BeginPlay();

	// TEST dynamic materials
	// UMaterialInstanceDynamic* DynamicMatInstance = StaticMesh->CreateAndSetMaterialInstanceDynamic(0);

	// if (DynamicMatInstance)
	// {
	// 	DynamicMatInstance->SetTextureParameterValue(FName("TextureMap"), TestTex);
	// }

}

// Called every frame
void ATestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATestCharacter::MyHttpCall()
{
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &ATestCharacter::OnResponseReceived);
	//This is the url on which to process the request
	Request->SetURL("http://localhost:8000/av.jpg");
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("image/jpeg"));
	Request->ProcessRequest();
}


// https://answers.unrealengine.com/questions/75929/is-it-possible-to-load-bitmap-or-jpg-files-at-runt.html
void ATestCharacter::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	TArray<uint8> ImageDataArray = Response->GetContent();
	UTexture2D* MyTex;

	UE_LOG(LogTemp, Warning, TEXT("ImageDataArray %d"), ImageDataArray.Num());

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
			UE_LOG(LogTemp, Warning, TEXT("Success"));
		}
	}


	UMaterialInstanceDynamic* DynamicMatInstance = StaticMesh->CreateAndSetMaterialInstanceDynamic(0);

	if (DynamicMatInstance)
	{
		DynamicMatInstance->SetTextureParameterValue(FName("TextureMap"), MyTex);
	}
}