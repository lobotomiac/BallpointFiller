// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UBoxComponent;

// TODO Make Getter and Setter methods for variables you're using!!
// TODO make a socket in HitBox to allow for automatic mesh placement
// TODO Set SpringArm NOT inherit MeshRotation



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

#if WITH_EDITOR
	// Called after some changes were made in the EU4 Editor
	virtual void PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent) override;
#endif // WITH_EDITOR


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
	UPROPERTY(EditAnywhere, Category = CameraControl)
	USpringArmComponent* SpringArm = nullptr;
	

	// Movement speed settings
	UPROPERTY(EditAnywhere, Category = "Controls")
	float MoveSensitivity = 200.0f;

	// Rotation speed settings
	UPROPERTY(EditAnywhere, Category = "Controls")
	float RotationSensitivity = 100.0f;

	// Camera Position Settings
	UPROPERTY(EditAnywhere, Category = "CameraControl")
	FVector SpringArmLocationOffset = FVector(0.0f, 0.0f, 50.0f);
	
	// SpringArm Rotation Settings
	UPROPERTY(EditAnywhere, Category = "CameraControl")
	FRotator SpringArmRotation = FRotator(-45.0f, 270.0f, 0.0f);

	// SpringArmLenght setting
	UPROPERTY(EditAnywhere, Category = "CameraControl")
	float SpringArmLength = 800.0f;

	// creating our StaticMesh for the Pawn body
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* PlayerMesh = nullptr;

	// adding a Collision Capsule component
	UPROPERTY(EditAnywhere)
	UBoxComponent* PlayerHitBox = nullptr;
	
	
};
