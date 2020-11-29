// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "AI/NavigationSystemBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"



void AShooterAIController:: BeginPlay()
{
    Super::BeginPlay();
    /*
    AIHeathBar=CreateDefaultSubobject<UWidgetComponent>(TEXT("Heath Bar"));
    
    UUserWidget* HeathBar=CreateWidget(this,HeathBarClass);
    if(HeathBarClass != nullptr)
    {
    AIHeathBar->SetWidget(HeathBar);
    }*/

    /*
    PlayerPawn=UGameplayStatics::GetPlayerPawn(GetWorld(),0);
    if(PlayerPawn != nullptr )
    {
        UE_LOG(LogTemp,Error,TEXT("The PlayerPawn of Index 0 It can not Found"))
        return;
    }   
    //this->SetFocus(PlayerPawn);
    UE_LOG(LogTemp,Error,TEXT("The SetFocuse is working"));
    */
    PlayerPawn=UGameplayStatics::GetPlayerPawn(GetWorld(),0);
    APawn* AIPawn=GetPawn();
    if(PlayerPawn == nullptr || AIPawn == nullptr)
    {
        UE_LOG(LogTemp,Error,TEXT("The PlayerPawn of Index 0 It can not Found")) 
        return;
    }
    if( AIPawn == nullptr)
    {
        UE_LOG(LogTemp,Error,TEXT("The AIPAwn of AI  It can not Found")) 
        return;
    } 
    if(AIBehavior != nullptr)
    {
        RunBehaviorTree(AIBehavior);
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"),AIPawn->GetActorLocation());
    }
    AIShooter= Cast<AShooterCharacter>(GetPawn());
    if(AIShooter == nullptr)
    {
        return;
    }
}

void AShooterAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    /*if(LineOfSightTo(PlayerPawn))
    {
        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"),PlayerPawn->GetActorLocation());
        GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownLocation"),PlayerPawn->GetActorLocation());
    }
    else
    {
        GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
        
    }*/

    /*if(LineOfSightTo(PlayerPawn))
    {
        SetFocus(PlayerPawn);
        MoveToActor(PlayerPawn,AcceptanceRedius);
    }
    else
    {
        ClearFocus(EAIFocusPriority::Gameplay);
        //Use this "MoveToLocation()" To Back to Start point then stop Movement 
        StopMovement();
        
    }*/
}


bool AShooterAIController::IsDead() const
{
	AShooterCharacter* ControllerCharacter=Cast<AShooterCharacter>(GetPawn());
    if(ControllerCharacter != nullptr)
    {
        return ControllerCharacter->IsDead();
    }
    return true;
}

float AShooterAIController::GetHealthOfEnemy() const
{
 

        return   AIShooter->GetHealth();
  
}
