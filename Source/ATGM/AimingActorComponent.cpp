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
	UE_LOG(LogTemp, Warning, TEXT("Begin Play"));
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
	if (!Barrel) return;
	FVector TargetLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	// UE_LOG(LogTemp, Display, TEXT("%s"), *TargetLocation.ToString());
	FVector BarrelLocation = Barrel->GetComponentLocation();
	auto Direction = (TargetLocation - BarrelLocation).GetSafeNormal();
	// DrawDebugLine(GetWorld(), BarrelLocation, BarrelLocation + Direction * 100000, FColor::Green, false, 0, 0, 10);

	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator DirectionRotation = Direction.Rotation();
	FRotator DeltaRotation = (DirectionRotation - BarrelRotation);
	// DrawDebugLine(GetWorld(), BarrelLocation, BarrelLocation + Barrel->GetForwardVector() * 100000, FColor::Blue, false, 0, 0, 10);

	
	TurretAimToTarget(DeltaRotation, DeltaTime);
	BarrelAimToTarget(DeltaRotation, DeltaTime);
}

void UAimingActorComponent::TurretAimToTarget(FRotator DeltaRotation, float DeltaTime)
{

	if(!Turret) return;
	auto TurretRotatingAngle = Turret->GetComponentRotation().Yaw + (DeltaRotation.Yaw * DeltaTime);
	Turret->SetRelativeRotation(FRotator(0, TurretRotatingAngle, 0));
}

void UAimingActorComponent::BarrelAimToTarget(FRotator DeltaRotation, float DeltaTime)
{
	if(!Barrel) return;
	auto BarrelElevatingAngle = Barrel->GetComponentRotation().Pitch + (DeltaRotation.Pitch * DeltaTime);

	if(BarrelElevatingAngle >= FMath::Clamp<float>(MinBarrelElevationAngle, 0, 40) && BarrelElevatingAngle <= FMath::Clamp<float>(MaxBarrelElevationAngle, 0, 40))
		Barrel->SetRelativeRotation(FRotator(BarrelElevatingAngle, 0, 0));
}

