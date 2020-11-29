// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "Gun_2.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AGun_2 : public AGun
{
	GENERATED_BODY()
		
	public:	
	// Sets default values for this actor's properties
	AGun_2();


	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	
	virtual void PullTrigger() override;

	
	bool IsAttack;
	FTimerHandle Timer;

    UFUNCTION(BlueprintPure)
	bool IsAttacked();
};
