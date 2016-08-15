// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealStudy.h"
#include "MyPawn.h"

#define Pi 3.14F
#define MoveMentRange 250.0F
#define RotateRange 100.0F


// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	UCameraComponent *ourCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	ourVisibleModelComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	ourVisibleStopModelComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("StopSkeletalMeshComponent"));
	ourCamera->AttachTo(RootComponent);
	ourCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	ourCamera->SetRelativeRotation(FRotator(-20.0f, 0.0f, 0.0f));
	
	ourVisibleModelComponent->AttachTo(RootComponent);
	ourVisibleStopModelComponent->AttachTo(RootComponent);
}

void AMyPawn::MoveY(float moveRange)
{
	FRotator nowRotation = GetActorRotation();
	float seta = Pi / 180 * (nowRotation.Yaw + 90);
	currentVelocity.X = FMath::Clamp(moveRange, -1.0F, 1.0F) * MoveMentRange * FMath::Sin(seta);
	currentVelocity.Y = -FMath::Clamp(moveRange, -1.0F, 1.0F) * MoveMentRange * FMath::Cos(seta);
}

void AMyPawn::MoveX(float moveRange)
{
	//currentVelocity.Y = FMath::Clamp(moveRange, -10.0F, 10.0F) * 100.0F;
	currentRotation.Yaw = FMath::Clamp(moveRange, -1.0F, 1.0F) * RotateRange;
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	bool isMoved = false;
	if (!currentVelocity.IsZero())
	{
		FVector newLocation = GetActorLocation() + (currentVelocity * DeltaTime);
		SetActorLocation(newLocation);
		isMoved = true;
	}
	if (!currentRotation.IsZero())
	{
		FRotator newRotation = GetActorRotation() + (currentRotation * DeltaTime);
		SetActorRotation(newRotation);
		isMoved = true;
	}
	if (!isMoved)//dont move
	{
		if (!ourVisibleStopModelComponent->IsPlaying())
		{
			ourVisibleStopModelComponent->Play(false);
		}
		ourVisibleModelComponent->SetVisibility(isMoved, true);
		ourVisibleStopModelComponent->SetVisibility(!isMoved, true);
	}
	else//move
	{
		ourVisibleModelComponent->SetVisibility(isMoved, true);
		ourVisibleStopModelComponent->SetPosition(0.0F, true);
		ourVisibleStopModelComponent->SetVisibility(!isMoved, true);
	}
	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, TEXT("Hello World %d"), DeltaTime);
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	InputComponent->BindAxis("MoveX", this, &AMyPawn::MoveX);
	InputComponent->BindAxis("MoveY", this, &AMyPawn::MoveY);
	
}

