
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
		GetKorniteOperatorPawn()->GetCameraLocation(CameraLocation);
        

		auto StartLocation = CameraLocation;
		auto EndLocation = StartLocation + Crosshair_3D_Direction * Range;
		
		// DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 0, 0, 10);
		// UE_LOG(LogTemp, Warning, TEXT("%s"), *(Crosshair_3D_Direction * Range).ToString());

		bool IsHittingSomthing = GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility);
		if(!IsHittingSomthing) Hit.Location = EndLocation;
	}
}


ALauncherPawn* ALauncherPlayerController::GetKorniteOperatorPawn() const
{
	return Cast<ALauncherPawn>(GetPawn());
}
