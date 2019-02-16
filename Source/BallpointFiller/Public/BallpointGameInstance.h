// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BallpointGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BALLPOINTFILLER_API UBallpointGameInstance : public UGameInstance
{
	GENERATED_BODY()
	

public:
	int GetPlayerScore() const;
	
	void SetPlayerScore(int ScoreUpdate);

private:
	int PlayerScore;
};
