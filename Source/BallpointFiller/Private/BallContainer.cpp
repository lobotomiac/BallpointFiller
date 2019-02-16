// Fill out your copyright notice in the Description page of Project Settings.

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT(text),fstring))


#include "BallContainer.h"
#include "DrawDebugHelpers.h"
#include "BallpointGameInstance.h"

// TODO SetActor Visible in game
// TODO make a size setter for both actor scale and DrawDebugBox - GetActorScale() * factor for both



ABallContainer::ABallContainer()
{
	BallValue = 10;

}


void ABallContainer::BeginPlay()
{
	Super::BeginPlay();
	
	DrawDebugBox(GetWorld(), GetActorLocation(), GetActorScale() * 48, FColor::Cyan, true, -1.0, 0, 20);
	
	// Setting up initial point values for start of the game
	Score = 0;

}


void ABallContainer::OnOverlapBegins(class AActor* OverlappingActor, class AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this))
	{
		IncreaseScore();
	}
	else
	{
		print("ABallContainer::OnOverlapBegins missing OtherActor");
	}
}

// Notifying the player an Actor (Ball) leaves the TriggerBox
void ABallContainer::OnOverlapEnds(AActor* OverlappingActor, AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this))
	{
		DecreaseScore();
		print("Ball fell out of the Ballpit");
	}
	else
	{
		print("ABallContainer::OnOverlapEnds missing OtherActor");
	}
}

/// Change in score
void ABallContainer::IncreaseScore()
{	
	Score++;
	CalculatePlayerScore();
	print("ScoreIncreased");
}
void ABallContainer::DecreaseScore()
{
	Score--;
	CalculatePlayerScore();
	print("Score Decreased");
}


void ABallContainer::CalculatePlayerScore()
{
	int TotalScore;
	if (Score != 0)
	{
		TotalScore = BallValue * Score;
	}
	UBallpointGameInstance* BallpointGameInstance = Cast<UBallpointGameInstance>(GetGameInstance());
	if (BallpointGameInstance)
	{
		BallpointGameInstance->SetPlayerScore(TotalScore);
	}
}