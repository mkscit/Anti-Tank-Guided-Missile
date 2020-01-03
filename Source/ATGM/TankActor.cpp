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
	Pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
}

// Called every frame
void ATankActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// AimToMainPlayer();
}


void ATankActor::SetUp(UStaticMeshComponent* Body,  UStaticMeshComponent* Turret, UStaticMeshComponent* Barrel)
{
	this->Body = Body;
	this->Turret = Turret;
	this->Barrel = Barrel;
}

void ATankActor::Destroy(AActor* AttackSource)
{
	AMissile* Missile = nullptr;
	Missile = Cast<AMissile>(AttackSource);

	if(!Missile) return;

	
}

void ATankActor::MoveForward(/*UTrack* Track,*/ float Throttle)
{
	// if(!Body || !Track) return;
	
	// Force = Body->GetMass() * Body->GetForwardVector() * Acceleration * Throttle;
	// FVector Location = Track->GetComponentLocation();

	// Body->AddForceAtLocation(Force, Location);
}

void ATankActor::MoveBackward(/*UTrack* Track,*/ float Throttle)
{
	// Force = Body->GetMass() * Body->GetForwardVector() * Acceleration * (-Throttle);
	// FVector Location = Track->GetComponentLocation();

	// Body->AddForceAtLocation(Force, Location);
}

