// Fill out your copyright notice in the Description page of Project Settings.

#include "BallpointGameInstance.h"




int UBallpointGameInstance::GetPlayerScore() const
{
	return PlayerScore;
}

void UBallpointGameInstance::SetPlayerScore(int ScoreUpdate)
{
	
	UE_LOG(LogTemp, Warning, TEXT("PlayerScore : %i"), ScoreUpdate)
}