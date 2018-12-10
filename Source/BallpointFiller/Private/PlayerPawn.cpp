// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"

// TODO Comment on CODE!!!!
// TODO learn about QUATERNIONS


// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Possessing the spawning pawn
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Creating the Pawn components
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	
	// Creating and setting the Mesh component (assign in Editor)
	VisibleControlledComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Our Mesh"));
	VisibleControlledComponent->SetupAttachment(RootComponent);
	
	// SpringArm  & Camera Settings

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetWorldRotation(SpringArmRotation);
	SpringArm->SetRelativeLocation(SpringArmLocationOffset);
	SpringArm->TargetArmLength = SpringArmLength;
	
	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Our Camera"));
	OurCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Moving Pawn if the required movement buttons are pressed
	if (!CurrentVelocity.IsZero())
	{
		// Changes Pawn position
		FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
		SetActorLocation(NewLocation);
	}
	if (!CurrentRotation.IsZero())
	{
		// Changes Pawn Rotation
		FRotator NewRotation = GetActorRotation() + (CurrentRotation * DeltaTime);
		SetActorRelativeRotation(NewRotation);
	}
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Binds input keys to Updating position.x of Pawn
	InputComponent->BindAxis("MoveRight", this, &APlayerPawn::MoveXAxis);
	InputComponent->BindAxis("TurnRight", this, &APlayerPawn::RotatePawn);
}


void APlayerPawn::MoveXAxis(float AxisValue)
{
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * MoveSensitivity;
}

void APlayerPawn::RotatePawn(float RotationValue)
{
	CurrentRotation.Yaw = FMath::Clamp(RotationValue, -1.0f, 1.0f) * RotationSensitivity;
}
