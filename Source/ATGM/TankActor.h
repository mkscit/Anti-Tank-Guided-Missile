// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "DrawDebugHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TankActor.generated.h"

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

	UFUNCTION(BlueprintCallable, Category = "TankActor Setup")
		void SetUp(UStaticMeshComponent* Body, UStaticMeshComponent* Turret, UStaticMeshComponent* Barrel);

	UFUNCTION(BlueprintCallable, Category = "Tank Distruction")
		void Destroy(AActor* AttackSource);

	void MoveForward(float Throttle);
	void MoveBackward(float Throttle);

	UStaticMeshComponent* Body = nullptr;
	UStaticMeshComponent* Turret = nullptr;
	UStaticMeshComponent* Barrel = nullptr;

	void AimToMainPlayer();
	
	FVector Force;
	

	UPROPERTY(EditAnywhere, Category = "Setup")
		float Acceleration = 10;

	APawn* Pawn = nullptr;

	void GetTargetDirection(FVector& Direction, FVector TargetLocation);
	void TurretAimToDirection(FRotator DeltaRotation);
	void BarrelAimToDirection(FRotator DeltaRotation);

};