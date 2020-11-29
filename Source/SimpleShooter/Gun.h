// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundBase.h"
#include "Gun.generated.h"

class AProjectile_Gun; 

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();
	virtual void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UParticleSystem* ParticleShoot;
	UPROPERTY(EditAnywhere)
	USoundBase* MuzzleSound;
	
	UPROPERTY(EditAnywhere)
	UParticleSystem* ParticleHit;
	UPROPERTY(EditAnywhere)
	USoundBase*  ParticleSound;
	

	float MaxRange=1000;
	
	UPROPERTY(EditAnywhere)
	float Damage=10.f;

	bool GunTrace(FHitResult &Hit,FVector& ShotRotation);
	
	AController* GetOwnerController() const;


	

	bool IsActive;
    public:
	 USkeletalMeshComponent* SkeletalGun();
	UPROPERTY(EditDefaultsOnly,Category="Projectile For Second Gun")
	TSubclassOf<AProjectile_Gun> ProjectileSecondGun;
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SpawnProjectilePoint;
	UPROPERTY(VisibleAnywhere)
	USphereComponent* CollectionInterract;

	void Interacted();
	bool GetActive();
// Create function when Player drop the Gun To Set the value of ISActive =True
	void DestroyMethod();

	void DisapleEnapleOverlapEvent(bool Enabled);

};
