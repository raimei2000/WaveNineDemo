#include "SpawnBoard.h"
#include "Trap.h"
#include "NineGameInstance.h"
#include "Components/BoxComponent.h"

ASpawnBoard::ASpawnBoard()
{
	PrimaryActorTick.bCanEverTick = false;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(RootScene);

	SpawnBoard = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBoard"));
	SpawnBoard->SetupAttachment(RootScene);

	SpawnDelay = 2.5f;
}

void ASpawnBoard::Activate(float Z)
{
	SizeX = SpawnBoard->GetScaledBoxExtent().X;
	SizeY = SpawnBoard->GetScaledBoxExtent().Y;
	SpawnZ = Z;
	OriginLocation = GetActorLocation();

	GetWorldTimerManager().SetTimer(SpawnSpikeTimerHandle, this, &ASpawnBoard::SpawnTrap, SpawnDelay, true);
}

FName ASpawnBoard::GetTrapName() const
{
	return TrapName;
}

FVector2D ASpawnBoard::GetRandomPointOnBoard() const
{
	return FVector2D(
		FMath::FRandRange(OriginLocation.X - SizeX, OriginLocation.X + SizeX),
		FMath::FRandRange(OriginLocation.Y - SizeY, OriginLocation.Y + SizeY));
}

void ASpawnBoard::SpawnTrap() const
{
	if (ActorToSpawn)
	{
		FVector2D Rand2DPoint = GetRandomPointOnBoard();
		GetWorld()->SpawnActor<ATrap>(ActorToSpawn, FVector(Rand2DPoint.X, Rand2DPoint.Y, SpawnZ), FRotator::ZeroRotator);
	}
}
