// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPaperSpriteActor.h"
#include "Engine/Texture2D.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "PaperSpriteComponent.h"

ATestPaperSpriteActor::ATestPaperSpriteActor()
{
	PaperSpriteComp = GetRenderComponent();

	// Texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> TexObj(TEXT("/Game/Textures/MY_UE4_LOGO"));
	TestTex = TexObj.Object;
}

void ATestPaperSpriteActor::BeginPlay()
{
	Super::BeginPlay();

	// TEST dynamic materials
	UMaterialInstanceDynamic* DynamicMatInstance = PaperSpriteComp->CreateAndSetMaterialInstanceDynamic(0);

	if (DynamicMatInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("DynamicMatInstance"));
		DynamicMatInstance->SetTextureParameterValue(FName("TextureMap"), TestTex);
	}
}