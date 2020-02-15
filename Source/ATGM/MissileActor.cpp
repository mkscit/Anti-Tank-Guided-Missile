// Fill out your copyright notice in the Description page of Project Settings.


#include "MissileActor.h"
#include "LauncherPlayerController.h"

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
	Explode();
}

void AMissileActor::Explode()
{
	if(!FrontPartOfMissile ) return;
	
	if(Fireball ) 
	// Stop the fire behined the FrontPartOfMissile.
	Fireball->Deactivate();

	if(Blast ) 
	// Particle of blast should be activated.
	Blast->Activate(true);

	if(ExplosionForce ) {
		// Activate the Radial force affecting to other objects.
		ExplosionForce->Activate(true);
		ExplosionForce->FireImpulse();
	}

	if(MissileBack )
	// Make the missile back to be physical.
	MissileBack->SetSimulatePhysics(true);

	// Set the missile back to be the root component. 
	SetRootComponent(MissileBack);

	// Destroy the front missile but it will be existing.
	FrontPartOfMissile->DestroyComponent();

	ExplosionForce->DestroyComponent();
	// Front missile should be null to remove completely.
	FrontPartOfMissile = nullptr;

	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AMissileActor::DestroyAfterCollision_TimeExpired, TimeToDestroyMissileAfterExplosion, false);
}
void AMissileActor::DestroyAfterCollision_TimeExpired()
{
	Destroy();
}

void AMissileActor::DestroyAfterLost_TimeExpired()
{
	Explode();
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
		auto DeltaTargetMissileRotation = TargetMissileRotation - MissileRotation;

		if(FMath::Abs(DeltaTargetMissileRotation.Yaw) <= MaxAngleOfMissileRotation && FMath::Abs(DeltaTargetMissileRotation.Pitch) <= MaxAngleOfMissileRotation)
		{
			auto Angle = DeltaTargetMissileRotation * DeltaTime * FMath::Clamp<float>(GuidingRate, 1, 1.5);
			auto Rotator = FrontPartOfMissile->GetComponentRotation() + Angle;
			FrontPartOfMissile->SetWorldRotation(Rotator);
		}
	}	
}

void AMissileActor::Move(float DeltaTime)
{
	if(!FrontPartOfMissile) return;
	auto Distance = Speed * DeltaTime;
	// FrontPartOfMissile->AddLocalTransform(FTransform(FVector(Distance, 0, 0)));
	FVector TargetLocation = LauncherPlayerController->Hit.Location;
	auto Value = FVector::DotProduct(TargetLocation.GetSafeNormal(), FrontPartOfMissile->GetComponentLocation().GetSafeNormal()) * (-1);
	FVector Force = FMath::Abs(  Value) * FrontPartOfMissile->GetMass() * Distance * FrontPartOfMissile->GetForwardVector();
	FrontPartOfMissile->AddForce(Force);

	if(!FrontPartOfMissile) return;
	FrontPartOfMissile->AddLocalRotation(FRotator(0, 0, RollSpeed * DeltaTime));
}