// Fill out your copyright notice in the Description page of Project Settings.

#include "unreal1.h"
#include "MyPawn.h"


// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	UCameraComponent *OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Our Camera"));
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	OurCamera->AttachTo(RootComponent);
	OurCamera->SetRelativeLocation(FVector(-250.0F, 0.0F, 250.0F));
	OurCamera->SetRelativeRotation(FRotator(-45.0F, 0.0F, 0.0F));
	OurVisibleComponent->AttachTo(RootComponent);
}

void AMyPawn::MoveYPoint(float yValue)
{
	CurrentVector.Y = FMath::Clamp(yValue, -1.0F, 1.0F) * 100.0F;
}

void AMyPawn::MoveXPoint(float xValue)
{
	CurrentVector.X = FMath::Clamp(xValue, -1.0F, 1.0F) * 100.0F;
}

void AMyPawn::StartGrowing()
{
	isGrowing = true;
}

void AMyPawn::StopGrowing()
{
	isGrowing = false;	
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
	if (!CurrentVector.IsZero())
	{
		FVector newLocation = GetActorLocation() + (CurrentVector * DeltaTime);
		SetActorLocation(newLocation);
	}

	float currentScale = OurVisibleComponent->GetComponentScale().X;
	if (isGrowing)
	{
		currentScale += DeltaTime;
	}
	else
	{
		currentScale -= DeltaTime;
	}

	currentScale = FMath::Clamp(currentScale, 1.0F, 2.0F);
	OurVisibleComponent->SetWorldScale3D(FVector(currentScale));
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	InputComponent->BindAction("Grow", IE_Pressed, this, &AMyPawn::StartGrowing);
	InputComponent->BindAction("Grow", IE_Released, this, &AMyPawn::StopGrowing);

	InputComponent->BindAxis("MoveY", this, &AMyPawn::MoveXPoint);
	InputComponent->BindAxis("MoveX", this, &AMyPawn::MoveYPoint);
}

