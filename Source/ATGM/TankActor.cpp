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
	MakeBigDestruction(AttackSource);
	// if(!AttackSource) return;
	// if(AttackSource != this)
	// UE_LOG(LogTemp, Warning, TEXT("DestroyWeakArea1 by %s"),*AttackSource->GetName());
}

void ATankActor::DestroyWeakArea2(AActor* AttackSource)
{
	MakeBigDestruction(AttackSource);
	// if(!AttackSource) return;
	// if(AttackSource != this)
	// UE_LOG(LogTemp, Warning, TEXT("DestroyWeakArea2 by %s"),*AttackSource->GetName());
}

void ATankActor::MakeBigDestruction(AActor* AttackSource)
{
	AMissileActor* Missile = nullptr;
	if(!AttackSource) return;
	Missile = Cast<AMissileActor>(AttackSource);

	if(!Missile) return;
	TArray<UActorComponent*> StaticMeshes = 
		GetComponentsByClass(UStaticMeshComponent::StaticClass());

	if (StaticMeshes.Num() > 0) {
		// LogTemp: Warning: 0 is Body
		// LogTemp: Warning: 1 is Light2
		// LogTemp: Warning: 2 is Barrel
		// LogTemp: Warning: 3 is Light1
		// LogTemp: Warning: 4 is Commander
		// LogTemp: Warning: 5 is Turret
		// LogTemp: Warning: 6 is GunnerSight
		// LogTemp: Warning: 7 is RightTrack
		// LogTemp: Warning: 8 is LeftTrack

		UStaticMeshComponent* Light1 = Cast<UStaticMeshComponent>(StaticMeshes[3]);
		UStaticMeshComponent* Light2 = Cast<UStaticMeshComponent>(StaticMeshes[1]);
		UStaticMeshComponent* GunnerSight = Cast<UStaticMeshComponent>(StaticMeshes[6]);
		UStaticMeshComponent* Commander = Cast<UStaticMeshComponent>(StaticMeshes[4]);
		Light1->SetSimulatePhysics(true);
		Light2->SetSimulatePhysics(true);
		GunnerSight->SetSimulatePhysics(true);
		Commander->SetSimulatePhysics(true);
		
		// UStaticMeshComponent* Barrel = Cast<UStaticMeshComponent>(StaticMeshes[2]);
		// UStaticMeshComponent* Turret = Cast<UStaticMeshComponent>(StaticMeshes[5]);
		// UStaticMeshComponent* RightTrack = Cast<UStaticMeshComponent>(StaticMeshes[7]);
		// UStaticMeshComponent* LeftTrack = Cast<UStaticMeshComponent>(StaticMeshes[8]);
		// Barrel->SetSimulatePhysics(true);
		// Turret->SetSimulatePhysics(true);
		// RightTrack->SetSimulatePhysics(true);
		// LeftTrack->SetSimulatePhysics(true);

		TArray<UActorComponent*> ParticleSystems = 
			GetComponentsByClass(UParticleSystemComponent::StaticClass());

		if (ParticleSystems.Num() > 0) {
			UParticleSystemComponent* Fire = Cast<UParticleSystemComponent>(ParticleSystems[0]);
			Fire->Activate();
			UParticleSystemComponent* Smoke = Cast<UParticleSystemComponent>(ParticleSystems[1]);
			Smoke->Activate();
			UParticleSystemComponent* Spark = Cast<UParticleSystemComponent>(ParticleSystems[2]);
			Spark->Activate();
		}

		TArray<UActorComponent*> Components = 
			GetComponentsByClass(UActorComponent::StaticClass());
		if (Components.Num() > 0) 
		{
			AimingComponent = Cast<UAimingActorComponent>(Components[0]);
			if (!AimingComponent) return;
			AimingComponent->DestroyComponent();
		}
	}
}
