// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Projectile_Gun.generated.h"

UCLASS()
class SIMPLESHOOTER_API AProjectile_Gun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile_Gun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
	USceneComponent* root;
	UPROPERTY(EditAnywhere)
    UStaticMeshComponent* ProjectileMesh;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UProjectileMovementComponent* ProjectileMov;;
};
