#include "NineGameState.h"
#include "SpawnVolume.h"
#include "BaseItem.h"
#include "BaseCoin.h"
#include "NineGameInstance.h"
#include "Kismet/GameplayStatics.h"

ANineGameState::ANineGameState()
{
    PrimaryActorTick.bCanEverTick = true;

    Score = 0;
    SpawnedCoinCount = 0;
    CollectedCoinCount = 0;
    LevelDuration = 10.f;
}

void ANineGameState::BeginPlay()
{
    Super::BeginPlay();

    if (UGameInstance* TempGameInst = GetGameInstance())
    {
        if (UNineGameInstance* NineGameInstance = Cast<UNineGameInstance>(TempGameInst))
        {
            GameInstance = NineGameInstance;
        }
    }

    StartLevel();

    MaxLevelIndex = LevelNames.Num() - 1;
}

void ANineGameState::OnCoinCollected(int32 score)
{
    CollectedCoinCount++;
    GameInstance->AddTotalScore(score);

    if (SpawnedCoinCount <= CollectedCoinCount)
    {
        EndLevel();
    }
}

void ANineGameState::EndLevel()
{
    GetWorldTimerManager().ClearTimer(LevelTimerHandle);

    if (GameInstance->GetCurrentLevelIndex() < MaxLevelIndex)
    {
        GameInstance->IncreaseLevelIndex();
        if (LevelNames.IsValidIndex(GameInstance->GetCurrentLevelIndex()))
        {
            UGameplayStatics::OpenLevel(GetWorld(), LevelNames[GameInstance->GetCurrentLevelIndex()]);
        }
    }
    else
    {
        OnGameOver();
        return;
    }
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
    }

    GetWorldTimerManager().SetTimer(LevelTimerHandle, this, &ANineGameState::EndLevel, LevelDuration, false);
}

void ANineGameState::Tick(float DeltaTime)
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(1, 0.f, FColor::Black, FString::Printf(TEXT("Coin: %d / %d"), CollectedCoinCount, SpawnedCoinCount));
        GEngine->AddOnScreenDebugMessage(3, 0.f, FColor::Yellow, FString::Printf(TEXT("Score: %d"), GameInstance->GetTotalScore()));
    }
}

void ANineGameState::OnGameOver()
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Game Over"));
    }
}
