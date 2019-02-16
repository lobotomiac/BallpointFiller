// Fill out your copyright notice in the Description page of Project Settings.

#include "BallSpawner.h"


// Sets default values
ABallSpawner::ABallSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Get a starting anchor point for spawner
	
}

// Called when the game starts or when spawned
void ABallSpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnerStartingPosition = GetActorLocation();
	
	// Will call SpawnBall after the specified time
	GetWorld()->GetTimerManager().SetTimer(OutHandle, this, &ABallSpawner::SpawnBall, SpawnInterval);

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
		
		// Changing the Spawn timer to makes sure its random for each ball
		UpdateSpawnInterval();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Ball"))
	}
	// calls the timer again with a randomized SpawnInterval
	GetWorld()->GetTimerManager().SetTimer(OutHandle, this, &ABallSpawner::SpawnBall, SpawnInterval);
}

//  changes position of spawner on the X plane
void ABallSpawner::UpdateSpawnerLocation()
{
	// setting a seed for random location change 
	FRandomStream RandomStream;
	RandomStream.GenerateNewSeed();
	// random range of change in spawner position
	float PositionChange = RandomStream.FRandRange(-PositionChangeRange, PositionChangeRange);

	// updates spawner location
	FVector NewSpawnerLocation = FVector(SpawnerStartingPosition.X + PositionChange, SpawnerStartingPosition.Y, SpawnerStartingPosition.Z);
	SetActorLocation(NewSpawnerLocation);

}

// getting a random number to update SpawnInterval
void ABallSpawner::UpdateSpawnInterval()
{
	float RandomValue = FGenericPlatformMath::FRand();

	if (!RandomValue)
	{
		SpawnInterval = 0.2f;
	}
	else
	{
		SpawnInterval = RandomValue * SpawnIntervalMultiplier;
	}
		
}
