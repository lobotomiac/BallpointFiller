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
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FVector SpawnerStartingPosition;

	/*Blueprint Reference of Ball class*/
	UPROPERTY(EditDefaultsOnly, Category = "ActorSpawning")
	TSubclassOf<ABall> BP_Ball;

	/*Delay after the BP_Ball will get spawned*/
	UPROPERTY(EditDefaultsOnly, Category = ActorSpawning)
	float TimeToStartSpawn = 2.0f;

	//  a constant spawn rate after initial spawn
	UPROPERTY(EditDefaultsOnly, Category = ActorSpawning)
	float SpawnInterval = 0.2f;
	
	/*Spawns the Ball_BP*/
	UFUNCTION()
	void SpawnBall();

	void UpdateSpawnerLocation();


};
