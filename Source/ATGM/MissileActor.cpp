// Fill out your copyright notice in the Description page of Project Settings.


#include "MissileActor.h"

// Sets default values
AMissileActor::AMissileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMissileActor::BeginPlay()
{
	Super::BeginPlay();
	
	LauncherPlayerController = Cast<ALauncherPlayerController>(GetWorld()->GetFirstPlayerController());
	FrontPartOfMissile = Cast<UPrimitiveComponent>(GetRootComponent());
	FrontPartOfMissile->OnComponentHit.AddDynamic(this, &AMissileActor::OnHit);

	TArray<UActorComponent*> StaticMeshes = 
		GetComponentsByClass(UStaticMeshComponent ::StaticClass());
	if (StaticMeshes.Num() > 0) {
		MissileBack = Cast<UStaticMeshComponent>(StaticMeshes[1]);
	}


	TArray<UActorComponent*> RadialForces = 
		GetComponentsByClass(URadialForceComponent ::StaticClass());
	if (RadialForces.Num() > 0) {
		ExplosionForce = Cast<URadialForceComponent>(RadialForces[0]);
	}

	TArray<UActorComponent*> ParticleSystems = 
		GetComponentsByClass(UParticleSystemComponent ::StaticClass());
	if (ParticleSystems.Num() > 0) {
		Fireball = Cast<UParticleSystemComponent>(ParticleSystems[0]);
		Blast = Cast<UParticleSystemComponent>(ParticleSystems[1]);
	}

	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AMissileActor::DestroyAfterLost_TimeExpired, TimeToDestroyMissileAfterLost, false);

}

// Called every frame
void AMissileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!LauncherPlayerController || !FrontPartOfMissile) return;

	ReGuidingMissile(DeltaTime);
	Move(DeltaTime);
}


void AMissileActor::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	
	// Stop the fire behined the FrontPartOfMissile.
	Fireball->Deactivate();

	// Activate the Radial force affecting to other objects.
	ExplosionForce->Activate(true);
	ExplosionForce->FireImpulse();
	
	// Destroy the target.
	DestroyTheTarget(OtherActor);

	// Particle of blast should be activated.
	Blast->Activate(true);

	// Make the missile back to be physical.
	MissileBack->SetSimulatePhysics(true);

	// Set the missile back to be the root component. 
	SetRootComponent(MissileBack);

	// Destroy the front missile but it will be existing.
	FrontPartOfMissile->DestroyComponent();

	// Front missile should be null to remove completely.
	FrontPartOfMissile = nullptr;

	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AMissileActor::DestroyAfterCollision_TimeExpired, TimeToDestroyMissileAfterExplosion, false);
}

void AMissileActor::DestroyTheTarget(AActor* Target)
{
	UE_LOG(LogTemp, Warning, TEXT("Destroy the %s"), *Target->GetName());

	// ATankActor* Tank = nullptr;
	// Tank = Cast<ATankActor>(Target);
	// if(!Tank) return;

	// UE_LOG(LogTemp, Warning, TEXT("Target is %s"), *Target->GetName());
	
	// TArray<UActorComponent*> StaticMeshes = 
	// 	Tank->GetComponentsByClass(UStaticMeshComponent::StaticClass());

	// // UE_LOG(LogTemp, Warning, TEXT("Count =  %d"), StaticMeshes.Num());
	// if (StaticMeshes.Num() > 0) {
	// 	// UE_LOG(LogTemp, Warning, TEXT("0 is %s"), *StaticMeshes[0]->GetName());
	// 	// UE_LOG(LogTemp, Warning, TEXT("1 is %s"), *StaticMeshes[1]->GetName());
	// 	// UE_LOG(LogTemp, Warning, TEXT("2 is %s"), *StaticMeshes[2]->GetName());
	// 	// UE_LOG(LogTemp, Warning, TEXT("3 is %s"), *StaticMeshes[3]->GetName());
	// 	// UE_LOG(LogTemp, Warning, TEXT("4 is %s"), *StaticMeshes[4]->GetName());
	// 	// UE_LOG(LogTemp, Warning, TEXT("5 is %s"), *StaticMeshes[5]->GetName());
	// 	// UE_LOG(LogTemp, Warning, TEXT("6 is %s"), *StaticMeshes[6]->GetName());
	// 	// UE_LOG(LogTemp, Warning, TEXT("7 is %s"), *StaticMeshes[7]->GetName());
	// 	// UE_LOG(LogTemp, Warning, TEXT("8 is %s"), *StaticMeshes[8]->GetName());

	// 	/*
	// 		LogTemp: Warning: 0 is Turret
	// 		LogTemp: Warning: 1 is Body
	// 		LogTemp: Warning: 2 is LeftTrack
	// 		LogTemp: Warning: 3 is RightTrack
	// 		LogTemp: Warning: 4 is Commander
	// 		LogTemp: Warning: 5 is Barrel
	// 		LogTemp: Warning: 6 is GunnerSight
	// 		LogTemp: Warning: 7 is Light1
	// 		LogTemp: Warning: 8 is Light2
	// 	*/

	// 	UStaticMeshComponent* Light1 = Cast<UStaticMeshComponent>(StaticMeshes[7]);
	// 	UStaticMeshComponent* Light2 = Cast<UStaticMeshComponent>(StaticMeshes[8]);
	// 	UStaticMeshComponent* GunnerSight = Cast<UStaticMeshComponent>(StaticMeshes[6]);
	// 	UStaticMeshComponent* Commander = Cast<UStaticMeshComponent>(StaticMeshes[4]);

		
	// 	//UStaticMeshComponent* Barrel = Cast<UStaticMeshComponent>(StaticMeshes[2]);
	// 	//UStaticMeshComponent* Turret = Cast<UStaticMeshComponent>(StaticMeshes[4]);
	// 	//UStaticMeshComponent* RightTrack = Cast<UStaticMeshComponent>(StaticMeshes[7]);
	// 	//UStaticMeshComponent* LeftTrack = Cast<UStaticMeshComponent>(StaticMeshes[8]);

	// 	Light1->SetSimulatePhysics(true);
	// 	Light2->SetSimulatePhysics(true);
	// 	GunnerSight->SetSimulatePhysics(true);
	// 	Commander->SetSimulatePhysics(true);

		
	// 	//Barrel->SetSimulatePhysics(true);
	// 	//Turret->SetSimulatePhysics(true);
	// 	// RightTrack->SetSimulatePhysics(true);
	// 	// LeftTrack->SetSimulatePhysics(true);


	// }

	// TArray<UActorComponent*> ParticleSystems = 
	// 	Tank->GetComponentsByClass(UParticleSystemComponent::StaticClass());

	// if (ParticleSystems.Num() > 0) {
	// 	UParticleSystemComponent* Fire = Cast<UParticleSystemComponent>(ParticleSystems[0]);
	// 	Fire->Activate();
	// 	UParticleSystemComponent* Smoke = Cast<UParticleSystemComponent>(ParticleSystems[1]);
	// 	Smoke->Activate();
	// 	UParticleSystemComponent* Spark = Cast<UParticleSystemComponent>(ParticleSystems[2]);
	// 	Spark->Activate();
	// }
}

void AMissileActor::DestroyAfterCollision_TimeExpired()
{
	Destroy();
}

void AMissileActor::DestroyAfterLost_TimeExpired()
{
	Destroy();
}

void AMissileActor::ReGuidingMissile(float DeltaTime)
{
	if(!FrontPartOfMissile) return;
	
	if(LauncherPlayerController->Hit.GetActor() != this)
	{
		FVector TargetLocation = LauncherPlayerController->Hit.Location;
		auto MissileLocation = GetActorLocation();
		auto TargetMissileDirection = (TargetLocation - MissileLocation).GetSafeNormal();

		auto TargetMissileRotation = TargetMissileDirection.Rotation();
		auto MissileRotation = FrontPartOfMissile->GetForwardVector().Rotation();
		auto TargetMissileRotation = TargetMissileRotation - MissileRotation;

		if(FMath::Abs(TargetMissileRotation.Yaw) <= MaxAngleOfMissileRotation && FMath::Abs(TargetMissileRotation.Pitch) <= MaxAngleOfMissileRotation)
		{
			auto Angle = TargetMissileRotation * DeltaTime * FMath::Clamp<float>(GuidingRate, 1, 1.5);
			auto Rotator = FrontPartOfMissile->GetComponentRotation() + Angle;
			FrontPartOfMissile->SetWorldRotation(Rotator);
		}
	}	
}

void AMissileActor::Move(float DeltaTime)
{
	if(!FrontPartOfMissile) return;
	
	auto Distance = Speed * DeltaTime;
	FrontPartOfMissile->AddLocalTransform(FTransform(FVector(Distance, 0, 0)));

	FrontPartOfMissile->AddLocalRotation(FRotator(0, 0, RollSpeed * DeltaTime));
}