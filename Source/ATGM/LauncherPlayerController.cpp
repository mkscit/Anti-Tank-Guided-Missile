
#include "LauncherPlayerController.h"

void ALauncherPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AimAt();
}

void ALauncherPlayerController::AimAt()
{
	int32 OUT SizeX;
	int32 OUT SizeY;
	GetViewportSize(SizeX, SizeY);

	FVector2D CrosshairPositionOnScreen = FVector2D(SizeX * 0.5, SizeY * 0.5);


	if (DeprojectScreenPositionToWorld(CrosshairPositionOnScreen.X,
		CrosshairPositionOnScreen.Y, Crosshair_3D_Location, Crosshair_3D_Direction)) {

		if (!GetKorniteOperatorPawn()) return;

		FVector OUT CameraLocation;
		// GetKorniteOperatorPawn()->GetCameraLocation(CameraLocation);
        

		auto StartLocation = CameraLocation;
		auto EndLocation = StartLocation + Crosshair_3D_Direction * Range;
		// DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, -1, 0, 10);

		LineTracing(StartLocation, EndLocation);
	}
}

void ALauncherPlayerController::LineTracing(FVector& StartLocation, FVector& EndLocation)
{
	GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility);
	
	// auto HitActor = Hit.GetActor();
	// if(HitActor) UE_LOG(LogTemp, Warning, TEXT("Line Tracing hits %s"), *HitActor->GetName());
}

ALauncherPawn* ALauncherPlayerController::GetKorniteOperatorPawn() const
{
	return Cast<ALauncherPawn>(GetPawn());
}
