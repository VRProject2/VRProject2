// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

UCLASS()
class UNREALSTUDY_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditAnywhere)
	USceneComponent *ourVisibleModelComponent;
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent *ourVisibleStopModelComponent;
	UPROPERTY(EditAnywhere)
	USpringArmComponent *ourCameraSpringArm;
	UCameraComponent *ourCamera;

	void MoveX(float moveRange);
	void MoveY(float moveRange);
	void PitchCamera(float range);
	void YawCamera(float range);

	FVector currentVelocity;
	FVector cameraVector;
	FRotator currentRotation;
	bool visible;
};
