// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "BallContainer.generated.h"

/**
 * 
 */



UCLASS()
class BALLPOINTFILLER_API ABallContainer : public ATriggerBox
{
	GENERATED_BODY()
	
private:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY()
	int Score;

public:

	// constructor that sets default values to this actor's properties
	ABallContainer();

	// overlap began function
	UFUNCTION()
	void OnOverlapBegins(AActor* OverlappedActor, AActor* OtherActor);

	// overlap end function
	UFUNCTION()
	void OnOverlapEnds(AActor* OverlappedActor, AActor* OtherActor);

	// value of Balls entering or leaving the TriggerBox
	int BallValue;
	void IncreaseScore();
	void DecreaseScore();
	// Calculate and update the score
	void CalculatePlayerScore();
};
