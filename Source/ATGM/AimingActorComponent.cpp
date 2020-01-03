// Fill out your copyright notice in the Description page of Project Settings.


#include "AimingActorComponent.h"

// Sets default values for this component's properties
UAimingActorComponent::UAimingActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAimingActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAimingActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	AimToMainPlayer(DeltaTime);
}

void UAimingActorComponent::SetUp( UStaticMeshComponent* Turret, UStaticMeshComponent* Barrel)
{
	this->Turret = Turret;
	this->Barrel = Barrel;
}

void UAimingActorComponent::AimToMainPlayer(float DeltaTime)
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

void UAimingActorComponent::TurretAimToDirection(FRotator DeltaRotation)
{
	Turret->AddRelativeRotation(FRotator(0, DeltaRotation.Yaw, 0));
}

void UAimingActorComponent::BarrelAimToDirection(FRotator DeltaRotation)
{
	Barrel->AddRelativeRotation(FRotator(DeltaRotation.Pitch, 0, 0));
}

