// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override ;
	
	
	
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereCollection;
		

	void Shoot();
private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);
	void LookUp(float AxisValue);
	void LookRight(float AxisValue);

	UPROPERTY(EditAnywhere)
	float Ratch=75.f;

	UPROPERTY(EditDefaultsOnly,Category="Gun1")
	TSubclassOf<AGun> FirstGunClass;
	
	UPROPERTY(EditDefaultsOnly,Category="Gun1")
	TSubclassOf<AGun> SecondGunClass;

	UPROPERTY(EditDefaultsOnly,Category="Gun1")
	TSubclassOf<AGun> ThirdGunClass;
	
	UPROPERTY()
	AGun * FirstGun;
	UPROPERTY()
	AGun * SecondGun;
	UPROPERTY()
	AGun * ThirdGun;

	UPROPERTY()
	AGun * CurrentGun=nullptr;

	


	UPROPERTY(EditDefaultsOnly)
	float MaxHealth=100.f;
    UPROPERTY(VisibleAnywhere)
	float Health;

public:
	UFUNCTION(BlueprintPure)
	bool IsDead() const;
	UFUNCTION(BlueprintPure)
	float GetHealth() const;




	private:
	void DestroyPawn();
	
	void Interract();
	UPROPERTY(EditAnywhere)
	float RaduisRange=95.0;

	

	//UPROPERTY(EditAnywhere)
	//TArray<TSubclassOf<AGun>> ALLGun;

	void SwitchNextWeapons();
	void SwitchPreviousWeaPons();

	
    int32 WeaponIndex;
	TArray<AGun*> WeaponArray;
	public:
	AGun* CurrentGunTag();

	void SpawnGunSound();
	UPROPERTY(EditAnywhere)
	USoundBase* PickupSound;
	UPROPERTY(EditAnywhere)
	USoundBase* DropSound;
	UPROPERTY(EditAnywhere)
	USoundBase* SwitchedGunSound;
	UPROPERTY(EditAnywhere)
	USoundBase* EmptyWeapon;
	UPROPERTY(EditAnywhere)
	USoundBase* NoMoreWeapon;
	
    UFUNCTION(BlueprintCallable)
	bool IsSwordCurrentGun() ;
	
 bool IsSwordUsed=false;
	UFUNCTION(BlueprintCallable)
	AGun* ISSworedActor();

	UArrowComponent * PlayerFrontDircetion;
	UPROPERTY(EditAnyWhere)
	float DropDistance=200;
	void DropItems();
	AGun* DropCurrentGun;
	int CurrentGunIndex;
	UFUNCTION()
	void OnPlayerOverLapBegin(UPrimitiveComponent* OverlappedComp,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 otherbodyIndex,bool bFromSweep,const FHitResult& SweepResult );
	

	
};
