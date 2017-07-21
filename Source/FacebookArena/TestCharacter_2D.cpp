// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCharacter_2D.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"

#include "UObject/ConstructorHelpers.h"

#include "Engine/Texture2D.h"

// Sets default values
ATestCharacter_2D::ATestCharacter_2D()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PaperSpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PaperSpriteComp"));
	PaperSpriteComp->SetupAttachment(RootComponent);


	// Texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> TexObj(TEXT("/Game/Textures/MyFire"));
	TestTex = TexObj.Object;

	// Get sprite comp
	static ConstructorHelpers::FObjectFinder<UPaperSprite> SpriteObj(TEXT("/Game/Blueprints/NewPaperSprite"));
	Sprite = SpriteObj.Object;
	Sprite->RescaleSpriteData(TestTex);

	PaperSpriteComp->SetSprite(SpriteObj.Object);
}

// Called when the game starts or when spawned
void ATestCharacter_2D::BeginPlay()
{
	Super::BeginPlay();
	
	Sprite->RescaleSpriteData(TestTex);
}

// Called every frame
void ATestCharacter_2D::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATestCharacter_2D::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

