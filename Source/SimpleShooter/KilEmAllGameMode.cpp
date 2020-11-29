// Fill out your copyright notice in the Description page of Project Settings.


#include "KilEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"
#include "ShooterCharacter.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"


void AKilEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
    Super::PawnKilled(PawnKilled);
    
    APlayerController* PlayerController=Cast<APlayerController>(PawnKilled->GetController());
    


    //if(PlayerController != nullptr)
    //{
  
    //    EndGame(false);
        
    //}


    AShooterCharacter* PlayerPawn=Cast<AShooterCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
    if(PawnKilled == PlayerPawn)
    {
        PlayerController->GameHasEnded(nullptr,false);
        return;
    }
    
    for( AShooterAIController* Controller  : TActorRange<AShooterAIController>( GetWorld()))
    {
        if(!Controller->IsDead())
        {
            AIController=Controller;
            return;
        }
    }

    EndGame(true);

}

void AKilEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
for( AController* Controller :TActorRange<AController>(GetWorld()))
{

    bool bIsWinner=Controller->IsPlayerController() == bIsPlayerWinner;

    if(bIsWinner)
    {
        Controller->GameHasEnded(nullptr,bIsWinner);
    }
    
}

    return;
}