// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacter.h"
UBTTask_Shoot::UBTTask_Shoot()
{
    NodeName=TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AAIController* AIOwner=OwnerComp.GetAIOwner();
    if(AIOwner == nullptr)
    {
        UE_LOG(LogTemp,Error,TEXT("The AI Controller Doesn't Found"))
        return EBTNodeResult::Failed;
    }
    
    AShooterCharacter* Character= Cast<AShooterCharacter> ( AIOwner->GetPawn());
    //AShooterCharacter* PlayerPawn=Cast<AShooterCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
    if(Character == nullptr)
    {
        UE_LOG(LogTemp,Error,TEXT("The AI Character Equal to nullptr"))
        return EBTNodeResult::Failed;
    }
    //PlayerPawn->Shoot();
    Character->Shoot();

    return EBTNodeResult::Succeeded;
}