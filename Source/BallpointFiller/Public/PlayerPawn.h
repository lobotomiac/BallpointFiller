// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;
UCLASS()
class BALLPOINTFILLER_API APlayerPawn : public APawn
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this pawn's properties
	APlayerPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Movement Input Method
	void MoveXAxis(float AxisValue);

	// Rotation Input Method
	void RotatePawn(float RotationValue);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Input Variables
	FVector CurrentVelocity;
	FRotator CurrentRotation;


	// Camera controlls
	UCameraComponent* OurCamera = nullptr;

	// SpringArmComponent for helping with camera stabilization
	USpringArmComponent* SpringArm = nullptr;


	// Movement speed settings
	UPROPERTY(EditAnywhere, Category = "Controls")
	float MoveSensitivity = 100.0f;
	// Rotation speed settings
	UPROPERTY(EditAnywhere, Category = "Controls")
	float RotationSensitivity = 100.0f;

// Camera settings (commented to make it work outside of C++ as a UE4 component)
	// Camera Position Settings
	UPROPERTY(EditAnywhere, Category = "CameraControl")
	FVector SpringArmLocationOffset = FVector(0.0f, 0.0f, 0.0f);
	
	// SpringArm Rotation Settings
	UPROPERTY(EditAnywhere, Category = "CameraControl")
	FRotator SpringArmRotation = FRotator(-45.0f, 0.0f, 0.0f);

	// SpringArmLenght setting
	UPROPERTY(EditAnywhere, Category = "CameraControl")
	float SpringArmLength = 400.0f;


	// creating our Pawn base
	UPROPERTY(EditAnywhere)
	USceneComponent* VisibleControlledComponent = nullptr;
};
