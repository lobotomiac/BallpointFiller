// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.h"
#include "BallSpawner.generated.h"


// TODO clamp the possible location change of the spawner

UCLASS()
class BALLPOINTFILLER_API ABallSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABallSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	

private:
	/*Spawns the Ball_BP*/
	UFUNCTION()
	void SpawnBall();

	// handle for managing the timer
	FTimerHandle OutHandle;

	// Default position of the Ball spawning object
	FVector SpawnerStartingPosition;

	/*Blueprint Reference of Ball class*/
	UPROPERTY(EditDefaultsOnly, Category = "ActorSpawning")
	TSubclassOf<ABall> BP_Ball;

	// multiplier to change the ball spawn rate
	UPROPERTY(EditDefaultsOnly, Category = ActorSpawning)
	float SpawnIntervalMultiplier = 2.0f;

	// rate of spawning (mutated in cpp file)
	UPROPERTY(EditDefaultsOnly, Category = ActorSpawning)
	float SpawnInterval = 2.0f;

	//  randomizing the ball spawning interval
	void UpdateSpawnInterval();

	// Updating the ball spawning location
	void UpdateSpawnerLocation();

	// Range of the Spawner position change
	UPROPERTY(EditDefaultsOnly, Category = ActorSpawning)
	float PositionChangeRange = 425;
};
