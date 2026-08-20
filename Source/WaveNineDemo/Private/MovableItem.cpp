#include "MovableItem.h"
#include "Components/SphereComponent.h"

AMovableItem::AMovableItem()
{
	RotationSpeed = 90.f;
	MaxRange = 50.f;
	Period = 3.f;
	PhaseOffset = 0.f;
	RotationOffset = 0.f;
	RunningTime = 0.f;
}

void AMovableItem::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	const float SafeRange = FMath::Max(MaxRange, 1.f);
	EndLocation = StartLocation + FVector(0.f, 0.f, SafeRange);

	RunningTime = FMath::Max(PhaseOffset * Period, 0.f);
	Collision->SetRelativeRotation(FRotator(0.f, RotationOffset, 0.f));
}

void AMovableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move(DeltaTime);
	Rotate(DeltaTime);
}

void AMovableItem::Move(float DeltaTime)
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, FString::Printf(TEXT("ABaseItem::Move")));
	const float SafePeriod = FMath::Max(Period, KINDA_SMALL_NUMBER);
	RunningTime = FMath::Fmod(RunningTime + DeltaTime, SafePeriod);

	const float Alpha = RunningTime / (SafePeriod * 0.5f);
	const float T = (1 - FMath::Cos(Alpha * PI)) * 0.5f;

	SetActorLocation(FMath::Lerp(StartLocation, EndLocation, T));
}

void AMovableItem::Rotate(float DeltaTime)
{
	Collision->AddRelativeRotation(FRotator(0.f, RotationSpeed * DeltaTime, 0.f));
}
