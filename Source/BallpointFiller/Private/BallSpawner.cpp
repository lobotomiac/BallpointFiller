// Fill out your copyright notice in the Description page of Project Settings.

#include "BallSpawner.h"


// Sets default values
ABallSpawner::ABallSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Get a starting anchor point for spawner
	
}

// Called when the game starts or when spawned
void ABallSpawner::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle OutHandle;
	SpawnerStartingPosition = GetActorLocation();
	
	// Will call SpawnBall after the specified time
	GetWorld()->GetTimerManager().SetTimer(OutHandle, this, &ABallSpawner::SpawnBall, SpawnInterval, true, TimeToStartSpawn);

}

// Called every frame
void ABallSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// UE_LOG(LogTemp, Warning, TEXT("%f"), GetWorld()->GetTimeSeconds())
}

void ABallSpawner::SpawnBall()
{
	// If the BP_Ball is valid
	if (BP_Ball)
	{
		// Spawn parameters for the current spawn
		// We can use this for a number of options like disable collision or adjust the spawn position
		// if a collision is happening in the spawn point etc...
		FActorSpawnParameters SpawnParams;

		UpdateSpawnerLocation();
		
		// Actual Spawn. The following function returns a reference to the spawned actor
		ABall* BallRef = GetWorld()->SpawnActor<ABall>(BP_Ball, GetTransform(), SpawnParams);

		UE_LOG(LogTemp, Warning, TEXT("Spawned the Ball at %s"), *GetActorLocation().ToString())
	}
}

//  changes position of spawner on the X plane
void ABallSpawner::UpdateSpawnerLocation()
{
	// setting a seed for random location change 
	FRandomStream RandomStream;
	RandomStream.GenerateNewSeed();
	// random range of change in spawner position
	float PositionChange = RandomStream.FRandRange(-100.0f, 100.0f);

	UE_LOG(LogTemp, Warning, TEXT("Position changing by: %f"), PositionChange)

	// updates spawner location
	FVector NewSpawnerLocation = FVector(SpawnerStartingPosition.X + PositionChange, SpawnerStartingPosition.Y, SpawnerStartingPosition.Z);
	SetActorLocation(NewSpawnerLocation);

	// TODO spawn at random interwals

}

