// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleShooterGameModeBase.h"
#include "KilEmAllGameMode.generated.h"

/**
 * 
 */
class AShooterAIController;
UCLASS()
class SIMPLESHOOTER_API AKilEmAllGameMode : public ASimpleShooterGameModeBase
{
	GENERATED_BODY()
	public:
	virtual void PawnKilled(APawn* PawnKilled) override;
	AShooterAIController* AIController=nullptr;
	private:
	void EndGame(bool bIsPlayerWinner);
	
	
};
