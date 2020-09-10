// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"


APawnTurret::APawnTurret()
{

}

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);
	
}

void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APawnTurret::CheckFireCondition() 
{
	// If Player == null || is Dead THEN BAIL!!	
	if (!PlayerPawn) { return; }

	// IF Player IS in range THEN FIRE!! 
	if (ReturnDistanceToPlayer() <= FireRange) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Fire Condition Success"));
	}	
}

float APawnTurret::ReturnDistanceToPlayer()
{
	if (!PlayerPawn) { return 0.f; }
	return FVector::Distance(PlayerPawn->GetActorLocation(), GetActorLocation());
}