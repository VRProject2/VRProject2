// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealStudy.h"
#include "CountDown.h"


// Sets default values
ACountDown::ACountDown()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	countDownUI = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CountDownNumber"));
	countDownUI->SetHorizontalAlignment(EHTA_Center);
	countDownUI->SetWorldSize(150.0f);
	RootComponent = countDownUI;

	countDownTime = 3;
}

void ACountDown::UpdateTimerDisplay()
{
	countDownUI->SetText(FString::FromInt(FMath::Max(countDownTime, 0)));
}

void ACountDown::AdvanceTimer()
{
	countDownTime -= 1;
	UpdateTimerDisplay();
	if (countDownTime <= 0)
	{
		GetWorldTimerManager().ClearTimer(CountDownTimerHandler);
		CountDownHasFinished();
	}
}

void ACountDown::CountDownHasFinished()
{
	countDownUI->SetText(TEXT("END"));
}

// Called when the game starts or when spawned
void ACountDown::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 32.0f, FColor::Blue, TEXT("Hello World"));
	UpdateTimerDisplay();
	GetWorldTimerManager().SetTimer(CountDownTimerHandler, this, &ACountDown::AdvanceTimer, 1.0F, true);
}

// Called every frame
void ACountDown::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

