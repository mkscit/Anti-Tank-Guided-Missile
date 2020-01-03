// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "DrawDebugHelpers.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AimingActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ATGM_API UAimingActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAimingActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UFUNCTION(BlueprintCallable, Category = "Tank Aiming")
		void SetUp(UStaticMeshComponent* Turret, UStaticMeshComponent* Barrel);

	UPROPERTY(EditAnywhere, Category = "Setup")
		float MinBarrelElevationAngle = 0;

	UPROPERTY(EditAnywhere, Category = "Setup")
		float MaxBarrelElevationAngle = 40;

	void AimToMainPlayer(float DeltaTime);
	void TurretAimToTarget(FRotator DeltaRotation, float DeltaTime);
	void BarrelAimToTarget(FRotator DeltaRotation, float DeltaTime);


	UStaticMeshComponent* Turret = nullptr;
	UStaticMeshComponent* Barrel = nullptr;
};
