#include "NineGameState.h"
#include "SpawnVolume.h"
#include "BaseItem.h"
#include "BaseCoin.h"
#include "Kismet/GameplayStatics.h"

ANineGameState::ANineGameState()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ANineGameState::BeginPlay()
{
    Super::BeginPlay();

    StartLevel();
}

void ANineGameState::OnCoinCollected(int32 score)
{
    CollectedCoinCount++;
    AddScore(score);

    if (SpawnedCoinCount <= CollectedCoinCount)
    {
        EndLevel();
    }
}

void ANineGameState::AddScore(int32 score)
{
    Score += score;
}

void ANineGameState::EndLevel()
{
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
                ABaseItem* SpawnedItem = Volume->RandomSpawnItem();
                if (SpawnedItem && SpawnedItem->IsA(ABaseCoin::StaticClass()))
                {
                    SpawnedCoinCount++;
                }
            }
        }

        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Black, FString::Printf(TEXT("Level loaded. Coins: %d"), SpawnedCoinCount));
        }
    }
}

void ANineGameState::Tick(float DeltaTime)
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(1, 0.f, FColor::Black, FString::Printf(TEXT("Coin: %d / %d"), CollectedCoinCount, SpawnedCoinCount));
    }
}
