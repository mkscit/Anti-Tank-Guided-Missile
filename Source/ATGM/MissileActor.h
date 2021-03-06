// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
// #include "TankActor.h"
#include "Engine/World.h"
#include "Public/TimerManager.h"
#include "Components/PrimitiveComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MissileActor.generated.h"

class ALauncherPlayerController;
// class ATankActor;

UCLASS()
class ATGM_API AMissileActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMissileActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void DestroyAfterCollision_TimeExpired();
	void DestroyAfterLost_TimeExpired();
	void ReGuidingMissile(float DeltaTime);
	void Move(float DeltaTime);
	void Explode();
	
	UParticleSystemComponent*  Blast 			        = nullptr;
	UParticleSystemComponent*  Fireball                 = nullptr;
	URadialForceComponent*     ExplosionForce           = nullptr;
	UPrimitiveComponent* 	   FrontPartOfMissile       = nullptr;
	ALauncherPlayerController* LauncherPlayerController = nullptr;
	UStaticMeshComponent*      MissileBack              = nullptr;

	UPROPERTY(EditAnywhere, Category = "Setup")
		float TimeToDestroyMissileAfterExplosion = 30;

	UPROPERTY(EditAnywhere, Category = "Setup")
		float TimeToDestroyMissileAfterLost = 120;

	UPROPERTY(EditAnywhere, Category = "Setup")
		float Speed = 1000;

	UPROPERTY(EditAnywhere, Category = "Setup")
		float MaxAngleOfMissileRotation = 60;

	UPROPERTY(EditAnywhere, Category = "Setup")
		float GuidingRate = 1;

	UPROPERTY(EditAnywhere, Category = "Setup")
		float RollSpeed = 700;
		

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

};

