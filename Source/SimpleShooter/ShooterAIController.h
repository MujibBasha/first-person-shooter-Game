// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Components/WidgetComponent.h"

#include "ShooterAIController.generated.h"

/**
 * 
 */
class AShooterCharacter;
UCLASS()
class SIMPLESHOOTER_API AShooterAIController : public AAIController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:
    //UWidgetComponent* AIHeathBar;
	//TSubclassOf<UUserWidget> HeathBarClass;
	  
	virtual void Tick(float DeltaSeconds) override;
	APawn* PlayerPawn;

	bool IsDead() const;
	private:
	//UPROPERTY(EditAnywhere)
	//float AcceptanceRedius=100;
	UFUNCTION(BlueprintPure)
	float GetHealthOfEnemy()const ;
	
	AShooterCharacter* AIShooter;
	UPROPERTY(EditAnywhere)
	UBehaviorTree* AIBehavior;
};
