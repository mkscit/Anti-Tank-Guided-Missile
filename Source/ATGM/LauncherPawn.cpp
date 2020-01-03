
#include "LauncherPawn.h"

// Sets default values
ALauncherPawn::ALauncherPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlatfomSystem = CreateDefaultSubobject<UStaticMeshComponent>(FName("PlatfomSystem"));
	LaserGuidingSystem = CreateDefaultSubobject<UStaticMeshComponent>(FName("LaserGuidingSystem"));
	Launcher = CreateDefaultSubobject<UStaticMeshComponent>(FName("Launcher"));
	MissileLocation = CreateDefaultSubobject<UStaticMeshComponent>(FName("Missile"));

	SetRootComponent(PlatfomSystem);
	LaserGuidingSystem->SetupAttachment(PlatfomSystem);
	Launcher->SetupAttachment(LaserGuidingSystem);
	MissileLocation->SetupAttachment(Launcher);

}

// Called when the game starts or when spawned
void ALauncherPawn::BeginPlay()
{
	Super::BeginPlay();

	TArray<UActorComponent*> Cameras = 
		GetComponentsByClass(UCameraComponent::StaticClass());


	if (Cameras.Num() > 0) {
		ThirdPersonCAM2 = Cast<UCameraComponent>(Cameras[1]);
		ThirdPersonCAM1   = Cast<UCameraComponent>(Cameras[0]);
		FirstPersonCAM = Cast<UCameraComponent>(Cameras[2]);

		
	}
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

	PlayerInputComponent->BindAxis("Right_Left", this, &ALauncherPawn::Right_Left);
	PlayerInputComponent->BindAxis("Up_Down", this, &ALauncherPawn::Up_Down);
	PlayerInputComponent->BindAxis("ZoomIn", this, &ALauncherPawn::ZoomInOut);
	PlayerInputComponent->BindAxis("ZoomOut", this, &ALauncherPawn::ZoomInOut);
	PlayerInputComponent->BindAction("ShowFirstPersonCAM", EInputEvent::IE_Pressed, this, &ALauncherPawn::ShowFirstPersonCAM);
	PlayerInputComponent->BindAction("ShowThirdPersonCAM1", EInputEvent::IE_Pressed, this, &ALauncherPawn::ShowThirdPersonCAM1);
	PlayerInputComponent->BindAction("ShowThirdPersonCAM2", EInputEvent::IE_Pressed, this, &ALauncherPawn::ShowThirdPersonCAM2);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ALauncherPawn::Fire);
}

void ALauncherPawn::Right_Left(float Axis)
{
	if(!FirstPersonCAM || !ThirdPersonCAM1 || !ThirdPersonCAM2 || !LaserGuidingSystem) return;
	
	float Yaw = Axis * GetWorld()->DeltaTimeSeconds * CameraRotationSpeed;
	FRotator Rotation(0, Yaw, 0);

	LaserGuidingSystem->AddRelativeRotation(Rotation);
}

void ALauncherPawn::Up_Down(float Axis)
{
	if(!FirstPersonCAM || !ThirdPersonCAM1 || !ThirdPersonCAM2 || !LaserGuidingSystem) return;

	float Pitch = Axis * GetWorld()->DeltaTimeSeconds * CameraRotationSpeed;
	FRotator Rotation(Pitch, 0, 0);

	LaserGuidingSystem->AddRelativeRotation(Rotation);
}

void ALauncherPawn::ZoomInOut(float Axis)
{
	if (!FirstPersonCAM) return;

	if(FirstPersonCAM->IsActive())
	{
		float ZoomDegree = Axis * GetWorld()->DeltaTimeSeconds * CameraRotationSpeed;
		ZoomDegree = ZoomDegree + FirstPersonCAM->FieldOfView;
		ZoomDegree = FMath::Clamp<float>(ZoomDegree, 20, 90);
		FirstPersonCAM->SetFieldOfView(ZoomDegree);
	}
}

void ALauncherPawn::Fire()
{
	if(!FirstPersonCAM) return;

	if(FirstPersonCAM->IsActive())
	{
		FVector Location = MissileLocation->GetComponentLocation();
		FRotator Rotation = Launcher->GetComponentRotation();

		// if (!ensure(MissileActor_BP)) return;

		SetMissleInTheWorld(Location, Rotation);
	}
}

void ALauncherPawn::ShowFirstPersonCAM()
{
	if (!FirstPersonCAM && !ThirdPersonCAM1 && !ThirdPersonCAM2) return;
	FirstPersonCAM->Activate(true);
	ThirdPersonCAM1->Deactivate();
	ThirdPersonCAM2->Deactivate();
}

void ALauncherPawn::ShowThirdPersonCAM1()
{
	if (!FirstPersonCAM && !ThirdPersonCAM1 && !ThirdPersonCAM2) return;
	ThirdPersonCAM1->Activate(true);
	FirstPersonCAM->Deactivate();
	ThirdPersonCAM2->Deactivate();
}

void ALauncherPawn::ShowThirdPersonCAM2()
{
	if (!FirstPersonCAM && !ThirdPersonCAM1 && !ThirdPersonCAM2) return;
	ThirdPersonCAM2->Activate(true);
	FirstPersonCAM->Deactivate();
	ThirdPersonCAM1->Deactivate();
}

void ALauncherPawn::SetMissleInTheWorld(FVector Location, FRotator Rotation)
{
	Missile = GetWorld()->SpawnActor<AMissileActor>(
		MissileActor_BP,
		Location,
		Rotation
	);
}

void ALauncherPawn::GetCameraLocation(FVector& CameraLocation)
{
	if (FirstPersonCAM)
		CameraLocation = FirstPersonCAM->GetComponentLocation();
}



