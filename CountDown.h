// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "CountDown.generated.h"

UCLASS()
class UNREALSTUDY_API ACountDown : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACountDown();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	int32 countDownTime;
	UTextRenderComponent *countDownUI;
	void UpdateTimerDisplay();
	void AdvanceTimer();
	void CountDownHasFinished();
	FTimerHandle CountDownTimerHandler;
};
