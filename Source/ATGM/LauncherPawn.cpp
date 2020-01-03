// Fill out your copyright notice in the Description page of Project Settings.


#include "LauncherPawn.h"

// Sets default values
ALauncherPawn::ALauncherPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALauncherPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALauncherPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALauncherPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

