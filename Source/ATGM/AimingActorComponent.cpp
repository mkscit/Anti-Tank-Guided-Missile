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

	UE_LOG(LogTemp, Display, TEXT("Target Location is %s"), *TargetLocation.ToString());
	//FVector BarrelLocation = Barrel->GetComponentLocation();
	FVector TankLocation = GetOwner()->GetActorLocation();
	UE_LOG(LogTemp, Display, TEXT("Tank Location is %s"), *TankLocation.ToString());
	auto Direction = (TargetLocation - TankLocation).GetSafeNormal();
	UE_LOG(LogTemp, Warning, TEXT("Target Direction is %s"), *Direction.ToString());
	// DrawDebugLine(GetWorld(), BarrelLocation, BarrelLocation + Direction * 100000, FColor::Green, false, 0, 0, 10);

	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	UE_LOG(LogTemp, Warning, TEXT("Barrel Rotation is %s"), *BarrelRotation.ToString());
	FRotator DirectionRotation = Direction.Rotation();
	UE_LOG(LogTemp, Warning, TEXT("Direction Rotation is %s"), *DirectionRotation.ToString());
	FRotator DeltaRotation = (DirectionRotation - BarrelRotation);
	UE_LOG(LogTemp, Warning, TEXT("Delta Rotation is %s"), *DeltaRotation.ToString());
	// DrawDebugLine(GetWorld(), BarrelLocation, BarrelLocation + Barrel->GetForwardVector() * 100000, FColor::Blue, false, 0, 0, 10);

	
	TurretAimToTarget(DeltaRotation, DeltaTime);
	BarrelAimToTarget(DeltaRotation, DeltaTime);
}

void UAimingActorComponent::TurretAimToTarget(FRotator DeltaRotation, float DeltaTime)
{

	if(!Turret) return;

	UE_LOG(LogTemp, Error, TEXT("Current Turret Yaw is %f \t\t New Turret Yaw is %f \t\t DTime is %f \t\t (NYaw * DTime) is %f"), Turret->GetComponentRotation().Yaw, DeltaRotation.Yaw, DeltaTime, (DeltaRotation.Yaw * DeltaTime));
	auto TurretRotatingAngle = Turret->RelativeRotation.Yaw + (DeltaRotation.Yaw * DeltaTime);
	UE_LOG(LogTemp, Error, TEXT("TurretRotatingAngle is %f"), TurretRotatingAngle);
	Turret->SetRelativeRotation(FRotator(0, TurretRotatingAngle, 0));
	UE_LOG(LogTemp, Error, TEXT("Turret Rotation is %s"), *Turret->GetComponentRotation().ToString());
	UE_LOG(LogTemp, Warning, TEXT("==========================================="));
}

void UAimingActorComponent::BarrelAimToTarget(FRotator DeltaRotation, float DeltaTime)
{
	if(!Barrel) return;
	auto BarrelElevatingAngle = Barrel->RelativeRotation.Pitch + (DeltaRotation.Pitch * DeltaTime);

	if(BarrelElevatingAngle >= FMath::Clamp<float>(MinBarrelElevationAngle, 0, 40) && BarrelElevatingAngle <= FMath::Clamp<float>(MaxBarrelElevationAngle, 0, 40))
		Barrel->SetRelativeRotation(FRotator(BarrelElevatingAngle, 0, 0));
}

