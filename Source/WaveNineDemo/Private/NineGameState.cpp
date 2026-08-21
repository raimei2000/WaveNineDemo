#include "NineGameState.h"
#include "SpawnVolume.h"
#include "Kismet/GameplayStatics.h"

ANineGameState::ANineGameState()
{
}

void ANineGameState::BeginPlay()
{
    Super::BeginPlay();

    StartLevel();
}

void ANineGameState::StartLevel()
{
    TArray<AActor*> Volumes;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), Volumes);

    if (Volumes.Num() > 0) {
        const int32 ItemToSpawn = 40;

        for (int32 i = 0; i < ItemToSpawn; i++)
        {
            if (ASpawnVolume* Volume = Cast<ASpawnVolume>(Volumes[0]))
            {
                Volume->RandomSpawnItem();
            }
        }
    }
}
