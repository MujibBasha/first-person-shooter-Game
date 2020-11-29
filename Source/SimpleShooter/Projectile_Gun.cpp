// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile_Gun.h"
#include "Components/StaticMeshComponent.h"
// Sets default values
AProjectile_Gun::AProjectile_Gun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performa
	PrimaryActorTick.bCanEverTick = true;
	root=CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent=root;
	ProjectileMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMesh->SetupAttachment(root);
	
	ProjectileMov=CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	

}

// Called when the game starts or when spawned
void AProjectile_Gun::BeginPlay()
{
	Super::BeginPlay();
	//ProjectileMov->	
	
}

// Called every frame
void AProjectile_Gun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

