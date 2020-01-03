// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "LauncherPawn.h"
#include "Public/DrawDebugHelpers.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LauncherPlayerController.generated.h"

class ALauncherPawn;
UCLASS()
class ATGM_API ALauncherPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaSeconds) override;

	FVector OUT Crosshair_3D_Direction;
	FVector OUT Crosshair_3D_Location;
	
	FHitResult OUT Hit;

private:
	UPROPERTY(EditAnywhere, Category = "Setup")
		float Range = 400000;

	ALauncherPawn* GetKorniteOperatorPawn() const;

	void AimAt();
	void LineTracing(FVector& StartLocation, FVector& EndLocation);
};
