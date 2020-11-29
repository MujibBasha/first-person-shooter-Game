// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"


#include "DrawDebugHelpers.h"
#include "Projectile_Gun.h"
#include "ShooterCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root=CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent=Root;
	Mesh=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	SpawnProjectilePoint=CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	SpawnProjectilePoint->SetupAttachment(Mesh);
	CollectionInterract=CreateDefaultSubobject<USphereComponent>(TEXT("Collision sphere"));
	CollectionInterract->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();

	IsActive=true;
	Mesh->SetSimulatePhysics(true);
	
}


// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::Interacted()
{
IsActive=false;
SetActorHiddenInGame(true);
    
}

bool AGun::GetActive()
{
return IsActive;
}

void AGun:: PullTrigger()
{

	
	
		UGameplayStatics::SpawnEmitterAttached(ParticleShoot,Mesh,TEXT("MuzzleFlashSocket"));
		UGameplayStatics::SpawnSoundAttached(MuzzleSound,Mesh,TEXT("MuzzleFlashSocket"));
	
	FVector ShotRotation;
	FHitResult Hit;
// To Spawn Projectile From Second Gun When The Second Gun is Current Used from the Player
	AShooterCharacter*PawnBase=Cast<AShooterCharacter>(GetOwner());
	
	if(PawnBase !=nullptr && PawnBase->CurrentGunTag()->ActorHasTag("GunProjectile") )
	{
		UE_LOG(LogTemp,Error,TEXT("The projectile is Spawn into the Scene"))
		//USceneComponent* SpawnProjectilePoint=GetComponentByClass;
		FVector SpawnLocation=SpawnProjectilePoint->GetComponentLocation();
		UE_LOG(LogTemp,Error,TEXT("The Location %s"),*SpawnLocation.ToString())
    AProjectile_Gun* ProjectileSpawn=GetWorld()->SpawnActor<AProjectile_Gun>(ProjectileSecondGun,SpawnLocation,FRotator::ZeroRotator);

		//ProjectileSpawn->InitialLifeSpan();
	}
	
	bool bSuccess=GunTrace(Hit,ShotRotation);


	
	if(bSuccess)
	{
		
		//DrawDebugLine(GetWorld(),ShotRotation,Hit.Location,FColor::Red,true);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),ParticleHit,Hit.Location,ShotRotation.Rotation());
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(),ParticleSound,Hit.Location,FRotator::ZeroRotator);
		//DrawDebugPoint(GetWorld(),Hit.Location,10,FColor::Red,true);

         AActor* HitActor=Hit.GetActor();
		if(HitActor != nullptr)
		{
			FPointDamageEvent DamageEvent (Damage,Hit,ShotRotation,nullptr);
			AController* OwnerController =GetOwnerController() ;
		HitActor->TakeDamage(Damage,DamageEvent,OwnerController,this);
		}
		
	}

	
}
void AGun::DisapleEnapleOverlapEvent(bool Enabled)
{
	CollectionInterract->SetGenerateOverlapEvents(Enabled);
	Mesh->SetSimulatePhysics(Enabled);
}

bool AGun::GunTrace(FHitResult &Hit,FVector& ShotRotation)
{
	AController* OwnerController =GetOwnerController() ;
	if(OwnerController == nullptr) return false; 
	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location,Rotation);
	
	FVector EndTrace=Location+Rotation.Vector()*MaxRange;
	
	 ShotRotation=-Rotation.Vector();
	//FCollisionQueryParams  Tr (FName(),true,OwnerPawn);
	//Or
	FCollisionQueryParams ParmsIgnore;
	ParmsIgnore.AddIgnoredActor(this);
	APawn* OwnerPawn=Cast<APawn>(GetOwner());
	ParmsIgnore.AddIgnoredActor(OwnerPawn);
	//bool bSuc=GetWorld()->LineTraceSingleByChannel(Hit,Location,EndTrace,ECollisionChannel::ECC_Visibility,Tr);

	//Or Created By My self(ECollisionChannel) in unreal Editer
	return GetWorld()->LineTraceSingleByChannel(Hit,Location,EndTrace,ECollisionChannel::ECC_GameTraceChannel1,ParmsIgnore);
	
}
AController* AGun::GetOwnerController() const
{
	APawn* OwnerPawn=Cast<APawn>(GetOwner());
	if(OwnerPawn == nullptr)
	{
		return nullptr;
	}
	return OwnerPawn->GetController();
	
	
}

USkeletalMeshComponent* AGun::SkeletalGun()
{
	return Mesh;
}

void AGun::DestroyMethod()
{
	this->Destroy();
}