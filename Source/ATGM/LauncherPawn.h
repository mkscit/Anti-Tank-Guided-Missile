// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MissileActor.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "LauncherPawn.generated.h"

class ALauncherPlayerController;
class AMissileActor;

UCLASS()
class ATGM_API ALauncherPawn : public APawn
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this pawn's properties
	ALauncherPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void GetCameraLocation(FVector& CameraLocation);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
		TSubclassOf<AMissileActor> MissileActor_BP;

private:

	UPROPERTY(EditAnywhere, Category = "Setup")
		float CameraRotationSpeed = 10;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* Launcher = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* LaserGuidingSystem = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* PlatfomSystem = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* MissileLocation = nullptr;

	UCameraComponent* FirstPersonCAM = nullptr;
	
	UCameraComponent* ThirdPersonCAM1 = nullptr;

	UCameraComponent* ThirdPersonCAM2 = nullptr;



	AMissileActor* Missile = nullptr;

	void Right_Left(float Axis);
	void Up_Down(float Axis);
	void ZoomInOut(float Axis);
	void Fire();
	
	void ShowFirstPersonCAM();
	void ShowThirdPersonCAM1();
	void ShowThirdPersonCAM2();

	void SetMissleInTheWorld(FVector Location, FRotator Rotation);

	ALauncherPlayerController* LauncherPlayerController = nullptr;

};
