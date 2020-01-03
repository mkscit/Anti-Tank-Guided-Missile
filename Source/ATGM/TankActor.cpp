// Fill out your copyright notice in the Description page of Project Settings.


#include "TankActor.h"


// Sets default values
ATankActor::ATankActor()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATankActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATankActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATankActor::DestroyWeakArea1(AActor* AttackSource)
{
	AMissileActor* Missile = nullptr;
	Missile = Cast<AMissileActor>(AttackSource);

	if(!Missile) return;

	
}

void ATankActor::DestroyWeakArea2(AActor* AttackSource)
{
	AMissileActor* Missile = nullptr;
	Missile = Cast<AMissileActor>(AttackSource);

	if(!Missile) return;

	
}
