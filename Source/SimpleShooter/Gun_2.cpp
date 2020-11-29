// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun_2.h"
#include "TimerManager.h"


AGun_2::AGun_2()
{
    
}


void AGun_2::BeginPlay()
{
    Super::BeginPlay();
    IsAttack=false;
}

void AGun_2::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
}

void AGun_2::PullTrigger()
{
    Super::PullTrigger();
    UE_LOG(LogTemp,Error,TEXT("The PullTrigger Override is call"));
    IsAttack=true;
    //GetWorldTimerManager().SetTimer(Timer,&)
 }
  
 
bool AGun_2::IsAttacked()
{
return IsAttack;
}
    

