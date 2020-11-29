// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"

#include "DetailLayoutBuilder.h"
#include "Components/CapsuleComponent.h"
#include "../../../../Program Files/Epic Games/UE_4.24/Engine/Source/Runtime/Engine/Classes/Components/InputComponent.h"
#include "Engine/World.h"
#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "TimerManager.h"
#include "SimpleShooterGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ArrowComponent.h"



// Sets default values
AShooterCharacter::AShooterCharacter()
 {
  	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
 	PrimaryActorTick.bCanEverTick = true;
	SphereCollection=CreateDefaultSubobject<USphereComponent>(TEXT("Sphere pickup"));
	SphereCollection->AttachTo(RootComponent);
	SphereCollection->SetSphereRadius(100.0f);

	PlayerFrontDircetion=CreateDefaultSubobject<UArrowComponent>(TEXT ("Player Front Direction"));
	PlayerFrontDircetion->AttachTo(RootComponent);

	IsSwordUsed=false;
 }
 
 // Called when the game starts or when spawned
 void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	Health=MaxHealth;
	//RangeSphere=CreateDefaultSubobject<USphereComponent>(TEXT("Collection Range"));
	//RangeSphere->SetSphereRadius(RaduisRange);
	//RangeSphere->SetupAttachment(RootComponent);
	
	/*GetMesh()->HideBoneByName(TEXT("weapon_r"),EPhysBodyOp::PBO_None);
	*	for(int i=0;i<ALLGun.Num();i++)
	{	
	Gun1Ref=GetWorld()->SpawnActor<AGun>(ALLGun[i]);
	Gun1Ref->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("weaponSocket"));
	Gun1Ref->SetOwner(this);
	if(i>0)
	Gun1Ref->SetActorHiddenInGame(true);
	}*/
	GetMesh()->HideBoneByName(TEXT("weapon_r"),EPhysBodyOp::PBO_None);
	
	FirstGun=GetWorld()->SpawnActor<AGun>(FirstGunClass);
	if(FirstGun)
	{
		FirstGun->DisapleEnapleOverlapEvent(false);
		CurrentGun=FirstGun;
		WeaponArray.Add(FirstGun);
		WeaponIndex=0;
		
		FirstGun->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("weaponSocket"));
		FirstGun->SetOwner(this);

	}

/*
	SecondGun=GetWorld()->SpawnActor<AGun>(SecondGunClass);
	
	if(SecondGun)
	{
	
	WeaponArray.Add(SecondGun);
	SecondGun->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("weaponSocket"));
	SecondGun->SkeletalGun()->SetHiddenInGame(true);
	SecondGun->SetOwner(this);
	}
	*/
	//When Over lap Gun show to Player UI To Press a "F"  to pick up this gun
	//ToDo SphereCollection->OnComponentBeginOverlap.AddDynamic();
 }

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
    float DamageToApplied=Super::TakeDamage(DamageAmount,DamageEvent,EventInstigator,DamageCauser);
    DamageToApplied=FMath::Min(Health,DamageToApplied);
	Health -=DamageToApplied;
	UE_LOG(LogTemp,Error,TEXT("Health = %f"),Health);
    if(IsDead())
    {
    	ASimpleShooterGameModeBase* GameMode= GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();
    	if(GameMode != nullptr)
    	{
    		GameMode->PawnKilled(this);
    	}
    	//To Block Controller When the Pawn is Dead
    	DetachFromControllerPendingDestroy();
    	
    	//To Remove Capsule Component When the Pawn is Dead Without Kill the Mesh Of Player
	    GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	    //FTimerHandle Ti;
    	//GetWorldTimerManager().SetTimer(Ti,this,&AShooterCharacter::DestroyPawn,1.3f,false);

    
    }
	return DamageToApplied;
	
}
void AShooterCharacter::DestroyPawn()
{
	this->Destroy();
}
bool AShooterCharacter::IsDead() const
{
	
	return  Health <= 0 ;

}

float AShooterCharacter::GetHealth() const
{
	return Health/MaxHealth ;
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"),this,& AShooterCharacter:: MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"),this,&AShooterCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookRight"),this,&AShooterCharacter::LookRight);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"),this,&AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAction(TEXT("Jump"),IE_Pressed,this,& ACharacter::Jump);
    PlayerInputComponent->BindAxis(TEXT("LookUpRate"),this,& AShooterCharacter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"),this,&AShooterCharacter::LookRightRate);
	PlayerInputComponent->BindAction(TEXT("Shoot"),IE_Pressed,this,& AShooterCharacter::Shoot);
	PlayerInputComponent->BindAction(TEXT("PickUp"),IE_Pressed,this,&  AShooterCharacter::Interract);
	PlayerInputComponent->BindAction(TEXT("SwitchNextWeaPons"),IE_Pressed,this,&  AShooterCharacter::SwitchNextWeapons);
	PlayerInputComponent->BindAction(TEXT("SwitchPreviousWeaPons"),IE_Pressed,this,&  AShooterCharacter::SwitchPreviousWeaPons);
	PlayerInputComponent->BindAction(TEXT("Drop"),IE_Pressed,this,& AShooterCharacter::DropItems);
}
void  AShooterCharacter::DropItems()
{
  //Get the current Gun
	DropCurrentGun=CurrentGun;
	// get the Index of Current Gun in a "WeaponArray"
	//CurrentGunIndex=
	
	//Replace Current Gun to Next gun of This Gun
	//CurrentGun  = null ptr
	// set Value of WeaponIndex to current WeaponIndex -1
	//WeaponIndex=WeaponIndex-1;
	SwitchNextWeapons();
	//remove this gun From array after That Destroy this Actor or not to Kipp all number of Bullet and some property
	WeaponArray.Remove(DropCurrentGun);

	UE_LOG(LogTemp,Error,TEXT("After remove from array "))

	   FTransform PlayerFrontDir=PlayerFrontDircetion->GetComponentTransform();
	   FVector ForwardVector=PlayerFrontDircetion->GetForwardVector();
	FVector DropPoint=PlayerFrontDir.GetLocation() + ForwardVector * DropDistance;
	UE_LOG(LogTemp,Error,TEXT("Afterget ForwardVector "))
	//Get The Front direction of Player and add to this Direction some Vector(PlayerDirection.Location +  To  
	//spawn it in a front Direction of Player
	AGun * DropActor=GetWorld()->SpawnActor<AGun>(DropCurrentGun->GetClass(),DropPoint,PlayerFrontDir.Rotator());
	//DropActor->SetActorEnableCollision(true);
	if(DropActor != nullptr)
	{
		//to Enable Simulate physics and OverLap Event 
		DropActor->DisapleEnapleOverlapEvent(true);
	}
	
	UE_LOG(LogTemp,Error,TEXT("After Spawn at Drop "))
	//or call the Blueprint Class To this thing
	DropCurrentGun->DestroyMethod();
	UE_LOG(LogTemp,Error,TEXT("After Destroy from AGun "))
	
	
	
	
}

void AShooterCharacter::SwitchNextWeapons()
{
	if(CurrentGun)
	{
		if(WeaponArray.Num() <= WeaponIndex+1)
			WeaponIndex=-1;
	if(WeaponArray.Num() != 0)
	{
		UE_LOG(LogTemp,Log,TEXT("Inside of SwitchNextWeapons () method"))
		WeaponIndex=WeaponIndex+1;
		
		if(AGun* NextGun=WeaponArray[WeaponIndex])
		{
			UE_LOG(LogTemp,Log,TEXT("Inside of if(NextGun= ) method"))
			if(WeaponArray.Num()>WeaponIndex)//add condition to Know is this Gun is Pickup from the Player
			{
				//Play Sound When Switch a Weapon
				UGameplayStatics::SpawnSoundAttached(SwitchedGunSound,GetMesh(),FName("WitchedGunSocket"));
				UE_LOG(LogTemp,Log,TEXT("Secceed to Switched Gun "))
				CurrentGun->SkeletalGun()->SetHiddenInGame(true);
				CurrentGun=NextGun;
				CurrentGun->SkeletalGun()->SetHiddenInGame(false);
				if(CurrentGun->ActorHasTag("Sword"))
				{
					IsSwordUsed=true;
				}
				else
					IsSwordUsed=false;
				}
			}
			else
			{
				//Play Sound Tool to Player their is No More weapon
				UGameplayStatics::SpawnSoundAttached(NoMoreWeapon,GetMesh(),FName("WitchedGunSocket"));
				//WeaponIndex=WeaponIndex-1;
			}
		}
	}
	else
	{
	  CurrentGun=nullptr;
		//ToDo apllay Idle Animation
	}
	
	}
	//UE_LOG(LogTemp,Error,TEXT("Index = %f"),WeaponIndex)

void AShooterCharacter::SwitchPreviousWeaPons()
{
	if(CurrentGun)
	{
		if(WeaponIndex <= 0)
			WeaponIndex=WeaponArray.Num();
		if(WeaponArray.Num() != 0)
		{
			WeaponIndex=WeaponIndex-1;
		    
			if(AGun* NextGun=WeaponArray[WeaponIndex])
			{
				if(true)//add condition to Know is this Gun is Pickup from the Player
				{
					//Play Sound When Switch a Weapon if their are More than one Weapon
					if(WeaponArray.Num() !=1 )
					UGameplayStatics::SpawnSoundAttached(SwitchedGunSound,GetMesh(),FName("WitchedGunSocket"));
					else
					{
						//Play Sound When their is No More Weapon
						UGameplayStatics::SpawnSoundAttached(NoMoreWeapon,GetMesh(),FName("WitchedGunSocket"));
					}
					CurrentGun->SkeletalGun()->SetHiddenInGame(true);
					CurrentGun=NextGun;
					CurrentGun->SkeletalGun()->SetHiddenInGame(false);
					if(CurrentGun->ActorHasTag("Sword"))
					{
						IsSwordUsed=true;
					}
					else
						IsSwordUsed=false;
				}
				else
				{
					//Play Sound thats ther no more Weapon
					//WeaponIndex=WeaponIndex+1;
				}
			}
			
		}
		else{
		    CurrentGun=nullptr;
			//ToDo apllay Idle Animation
		}
	
	}
}

AGun* AShooterCharacter::CurrentGunTag()
{
	//To call this method from AGun To Add specific Effect to Projectile Gun
	return CurrentGun;
}


void AShooterCharacter::Interract()
{
	TArray<AActor*> inRangeItems;
	SphereCollection->GetOverlappingActors(inRangeItems);
	for(int i=0;i<inRangeItems.Num();i++)
	{
		UE_LOG(LogTemp,Error,TEXT("KNow we are inside of Interract function"))
		AGun* const Gun_Ref2=Cast<AGun>(inRangeItems[i]);
		
		if(Gun_Ref2 != nullptr)
		{
			UE_LOG(LogTemp,Error,TEXT("The Gun Is Pick up from the Player"))
			
		}
		if(Gun_Ref2 != nullptr && Gun_Ref2->GetActive() && !Gun_Ref2->IsPendingKill() )
		{

			//Play Sound When get the weapon from the Ground
			FVector PickupLocation=Gun_Ref2->GetActorLocation();
			UGameplayStatics::SpawnSoundAtLocation(GetWorld(),PickupSound,PickupLocation,FRotator::ZeroRotator);
			//Spawn UI Gun for This Gun
			Gun_Ref2->Interacted();
			
	
			AGun* Gun_Ref2Spawned=GetWorld()->SpawnActor<AGun>(Gun_Ref2->GetClass());
			
			//TODO Disable Simulate physics when pickup Gun]
			//Gun_Ref2Spawned->SimulatePysics
			if( Gun_Ref2Spawned != nullptr)
			{
				//Disaple  Overlap Event of Spawned gun To Save Us from Pickup The Same Weapon that pickup before (in my Bag gun)
				Gun_Ref2Spawned->DisapleEnapleOverlapEvent(false);
	
				WeaponArray.Add(Gun_Ref2Spawned);
				if(!Gun_Ref2Spawned->ActorHasTag(FName("Sword")))
				{
					Gun_Ref2Spawned->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("weaponSocket"));
				}
				else
				{
					Gun_Ref2Spawned->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("hand_r_Sword"));
				}
				
				Gun_Ref2Spawned->SkeletalGun()->SetHiddenInGame(true);
				Gun_Ref2Spawned->SetOwner(this);

			}
			SpawnGunSound();
		}
	}
	/*
	//Gun_Ref2->SetActorHiddenInGame(false);
	*TArray<AActor*>  inRangeItems;
	RangeSphere->GetOverlappingActors(inRangeItems);
	AGun* Gun_Ref2=Cast<AGun>(ALLGun[1]);
	Gun_Ref2->SetActorHiddenInGame(false);
	///
		for(int i=0 ; i<inRangeItems.Num();i++)
    {
    AGun* Gun_Pickup=Cast<AGun>(inRangeItems[i]);

    if(Gun_Pickup && Gun_Pickup->GetActive())
    {
    //Gun_Pickup->Interacted();
		
    //Gun_Pickup->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("weaponSocket"));
    //Gun_Pickup->SetOwner(this);
			
    }
		
    }
	 */
	
}
void AShooterCharacter::OnPlayerOverLapBegin(UPrimitiveComponent* OverlappedComp,AActor* Otheractor,UPrimitiveComponent* OtherComp,int32 otherbodyIndex,bool bFromSweep,const FHitResult& SweepResult )
{
	
}
void AShooterCharacter::SpawnGunSound()
{
	UE_LOG(LogTemp,Log,TEXT("The Gun Is Spawned in the Scene"))
}
	
void AShooterCharacter::Shoot()
{
   if(CurrentGun != nullptr)
   {
	   CurrentGun->PullTrigger();
   }
}
void AShooterCharacter:: MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector()*AxisValue);
	
}
void AShooterCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector()*AxisValue);
}
void AShooterCharacter::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}
void AShooterCharacter::LookRight(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}
void AShooterCharacter::LookUpRate(float AxisValue)
{
AddControllerPitchInput(AxisValue * GetWorld()->GetDeltaSeconds()* Ratch);
}

void AShooterCharacter::LookRightRate(float AxisValue)
{
AddControllerYawInput(AxisValue *Ratch * GetWorld()->GetDeltaSeconds());
}

bool AShooterCharacter::IsSwordCurrentGun() 
{
	
return IsSwordUsed;
}

AGun*  AShooterCharacter::ISSworedActor()
{
	return CurrentGun;
}
