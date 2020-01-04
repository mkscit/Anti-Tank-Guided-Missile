// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "AimingActorComponent.h"
#include "MissileActor.h"
#include "DrawDebugHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TankActor.generated.h"

// class AMissileActor;

UCLASS()
class ATGM_API ATankActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATankActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UFUNCTION(BlueprintCallable, Category = "Tank Distruction")
		void DestroyWeakArea1(AActor* AttackSource);

	UFUNCTION(BlueprintCallable, Category = "Tank Distruction")
		void DestroyWeakArea2(AActor* AttackSource);

	void MakeBigDestruction(AActor* AttackSource);

	UAimingActorComponent* AimingComponent = nullptr;

};