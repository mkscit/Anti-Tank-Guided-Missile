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

	TArray<UActorComponent*> StaticMeshes = 
		GetComponentsByClass(UStaticMeshComponent::StaticClass());

	if (StaticMeshes.Num() > 0) {
		UE_LOG(LogTemp, Warning, TEXT("0 is %s"), *StaticMeshes[0]->GetName());
		UE_LOG(LogTemp, Warning, TEXT("1 is %s"), *StaticMeshes[1]->GetName());
		UE_LOG(LogTemp, Warning, TEXT("2 is %s"), *StaticMeshes[2]->GetName());
		UE_LOG(LogTemp, Warning, TEXT("3 is %s"), *StaticMeshes[3]->GetName());
		UE_LOG(LogTemp, Warning, TEXT("4 is %s"), *StaticMeshes[4]->GetName());
		UE_LOG(LogTemp, Warning, TEXT("5 is %s"), *StaticMeshes[5]->GetName());
		UE_LOG(LogTemp, Warning, TEXT("6 is %s"), *StaticMeshes[6]->GetName());
		UE_LOG(LogTemp, Warning, TEXT("7 is %s"), *StaticMeshes[7]->GetName());
		UE_LOG(LogTemp, Warning, TEXT("8 is %s"), *StaticMeshes[8]->GetName());


		// LogTemp: Warning: 0 is Body
		// LogTemp: Warning: 1 is Light2
		// LogTemp: Warning: 2 is Barrel
		// LogTemp: Warning: 3 is Light1
		// LogTemp: Warning: 4 is Commander
		// LogTemp: Warning: 5 is Turret
		// LogTemp: Warning: 6 is GunnerSight
		// LogTemp: Warning: 7 is RightTrack
		// LogTemp: Warning: 8 is LeftTrack
	}
	
}

void ATankActor::DestroyWeakArea2(AActor* AttackSource)
{
	AMissileActor* Missile = nullptr;
	Missile = Cast<AMissileActor>(AttackSource);

	if(!Missile) return;

	TArray<UActorComponent*> StaticMeshes = 
		GetComponentsByClass(UStaticMeshComponent::StaticClass());

	if (StaticMeshes.Num() > 0) {
		UE_LOG(LogTemp, Warning, TEXT("0 is %s"), *StaticMeshes[0]->GetName());
		UE_LOG(LogTemp, Warning, TEXT("1 is %s"), *StaticMeshes[1]->GetName());
		UE_LOG(LogTemp, Warning, TEXT("2 is %s"), *StaticMeshes[2]->GetName());
		UE_LOG(LogTemp, Warning, TEXT("3 is %s"), *StaticMeshes[3]->GetName());
		UE_LOG(LogTemp, Warning, TEXT("4 is %s"), *StaticMeshes[4]->GetName());
		UE_LOG(LogTemp, Warning, TEXT("5 is %s"), *StaticMeshes[5]->GetName());
		UE_LOG(LogTemp, Warning, TEXT("6 is %s"), *StaticMeshes[6]->GetName());
		UE_LOG(LogTemp, Warning, TEXT("7 is %s"), *StaticMeshes[7]->GetName());
		UE_LOG(LogTemp, Warning, TEXT("8 is %s"), *StaticMeshes[8]->GetName());
	}
}
