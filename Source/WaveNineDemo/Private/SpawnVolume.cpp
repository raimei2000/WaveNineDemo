#include "SpawnVolume.h"
#include "Components/BoxComponent.h"

ASpawnVolume::ASpawnVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	SetRootComponent(RootScene);

	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	SpawnVolume->SetupAttachment(RootScene);

	SizeX = 0.f;
	SizeY = 0.f;
	SizeZ = 0.f;
	OriginLocation = FVector(0.f, 0.f, 0.f);
}

void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();

	FVector BoxSize = SpawnVolume->GetScaledBoxExtent();
	SizeX = BoxSize.X;
	SizeY = BoxSize.Y;
	SizeZ = BoxSize.Z;

	OriginLocation = GetActorLocation();
}

FVector ASpawnVolume::GetRandomPointInVolume()
{
	return FVector(
		FMath::FRandRange(OriginLocation.X - SizeX, OriginLocation.X + SizeX),
		FMath::FRandRange(OriginLocation.Y - SizeY, OriginLocation.Y + SizeY),
		FMath::FRandRange(OriginLocation.Z - SizeZ, OriginLocation.Z + SizeZ));
}
