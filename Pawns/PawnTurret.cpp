// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"


// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true, false);

    PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this,0));
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APawnTurret::CheckFireCondition()
{
    // If Player == null || is Dead THEN BAIL!!
    if (!PlayerPawn)
    {
        return;
    }
    // If Player Player IS  in range THEN FIRE!!
    if (ReturnDistanceToPlayer() <= FireRange)
    {
        //Fire
        UE_LOG(LogTemp, Warning, TEXT("FIRE!"));
    }
}

float APawnTurret::ReturnDistanceToPlayer()
{
    // Check if we have a valid reference to the player.
    if (!PlayerPawn)
    {
        return 0.0f;
    }

    float Distance = (PlayerPawn->GetActorLocation() - GetActorLocation()).Size();
    return Distance;
}