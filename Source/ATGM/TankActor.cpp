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

	AimToMainPlayer();
}


void ATankActor::SetUp(UStaticMeshComponent* Body,  UStaticMeshComponent* Turret, UStaticMeshComponent* Barrel)
{
	this->Body = Body;
	this->Turret = Turret;
	this->Barrel = Barrel;
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

void ATankActor::AimToMainPlayer()
{
	
	FVector TargetLocation = Pawn->GetActorLocation();
	FVector OUT Direction;
	GetTargetDirection(Direction, TargetLocation);
	
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator DirectionRotation = Direction.Rotation();
	FRotator DeltaRotation = DirectionRotation - BarrelRotation;

	TurretAimToDirection(DeltaRotation);
	BarrelAimToDirection(DeltaRotation);
}

void ATankActor::TurretAimToDirection(FRotator DeltaRotation)
{
	Turret->AddRelativeRotation(FRotator(0, DeltaRotation.Yaw, 0));
}

void ATankActor::BarrelAimToDirection(FRotator DeltaRotation)
{
	Barrel->AddRelativeRotation(FRotator(DeltaRotation.Pitch, 0, 0));
}

void ATankActor::GetTargetDirection(FVector& Direction, FVector TargetLocation)
{
	FVector BarrelLocation = Barrel->GetComponentLocation();
	Direction = (TargetLocation - BarrelLocation);
}