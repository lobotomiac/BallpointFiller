// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

// TODO Comment CODE!!!!
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
	RootComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 5.0f));

	// Creating and setting the Mesh component (assign in Editor)
	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Player Mesh"));
	PlayerMesh->SetupAttachment(RootComponent);
	
	PlayerMesh->SetSimulatePhysics(false);
	
	// Creating and Attaching the collision BoxComponent
	PlayerHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Player Hit Box"));
	PlayerHitBox->SetupAttachment(RootComponent);
	PlayerHitBox->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));

	// Creating SpringArm and Setting it up
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetWorldRotation(SpringArmRotation);
	SpringArm->SetRelativeLocation(SpringArmLocationOffset);
	SpringArm->TargetArmLength = SpringArmLength;
	SpringArm->bInheritYaw = false;

	// Creating a Camera
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


// Checking if the StaticMesh used for Pawn is changed and Updating the UBoxComponent dimensions to match the StaticMesh dimensions
#if WITH_EDITOR
void APlayerPawn::PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent)
{
	FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(APlayerPawn, PlayerMesh))
	{
		// geting the size of player StaticMesh body and adjusting the size of the BoxComponent to match it 
		auto PlayerMeshBounds = PlayerMesh->CalcBounds(GetActorTransform());
		auto PlayerMeshScale = PlayerMesh->GetComponentScale();
		PlayerHitBox->SetBoxExtent(PlayerMeshBounds.BoxExtent);
		PlayerHitBox->SetRelativeScale3D(PlayerMeshScale);
		// TODO Set to change the rotation as well // CHECK IF YOU"RE USING IT RIGHT - CHANCES ARE YOU AREN'T
		
		auto PlayerMeshRotation = PlayerMesh->GetComponentRotation();
		
		UE_LOG(LogTemp, Warning, TEXT("PostEditChangeProperty Called and did stuff"))
	}
	UE_LOG(LogTemp, Warning, TEXT("%s called PostEditChangeProperty without altering dimensions"), *PropertyName.ToString())

	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif // WITH_EDITOR
