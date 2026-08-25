#include "SpawnVolume.h"
#include "ItemSpawnRow.h"
#include "FloatArrayRow.h"
#include "Components/BoxComponent.h"

ASpawnVolume::ASpawnVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	SetRootComponent(RootScene);

	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	SpawnVolume->SetupAttachment(RootScene);

	ItemSpawnTable = nullptr;

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

FVector ASpawnVolume::GetRandomPointInVolume() const
{
	return FVector(
		FMath::FRandRange(OriginLocation.X - SizeX, OriginLocation.X + SizeX),
		FMath::FRandRange(OriginLocation.Y - SizeY, OriginLocation.Y + SizeY),
		FMath::FRandRange(OriginLocation.Z - SizeZ, OriginLocation.Z + SizeZ));
}

FItemSpawnRow* ASpawnVolume::GetRandomItem(int32 LevelIndex, int32 WaveIndex) const
{
	if (!ItemSpawnTable) return nullptr;

	TArray<FItemSpawnRow*> AllRows;
	ItemSpawnTable->GetAllRows(TEXT("ItemSpawnContext"), AllRows);

	if (AllRows.IsEmpty()) return nullptr;

	float TotalChance = 0.f;
	for (const auto Row : AllRows) TotalChance += Row->SpawnChance[LevelIndex][WaveIndex];

	const float RandNumber = FMath::FRandRange(0.f, TotalChance);
	float AccumulateChance = 0.f;

	for (const auto Row : AllRows)
	{
		AccumulateChance += Row->SpawnChance[LevelIndex][WaveIndex];
		if (RandNumber <= AccumulateChance)
		{
			return Row;
		}
	}

	return nullptr;
}

ABaseItem* ASpawnVolume::SpawnItem(TSubclassOf<ABaseItem> ItemClass) const
{
	if (!ItemClass) return nullptr;

	ABaseItem* SpawnedItem = GetWorld()->SpawnActor<ABaseItem>(
		ItemClass,
		GetRandomPointInVolume(),
		FRotator::ZeroRotator
	);
	return SpawnedItem;
}

ABaseItem* ASpawnVolume::RandomSpawnItem(int32 LevelIndex, int32 WaveIndex) const
{
	if (const FItemSpawnRow* SelectedRow = GetRandomItem(LevelIndex, WaveIndex))
	{
		if (UClass* ActualClass = SelectedRow->ItemClass.Get())
		{
			return SpawnItem(ActualClass);
		}
	}
	return nullptr;
}
