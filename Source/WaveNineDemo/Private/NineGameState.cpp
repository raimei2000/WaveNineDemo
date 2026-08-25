#include "NineGameState.h"
#include "SpawnVolume.h"
#include "BaseItem.h"
#include "BaseCoin.h"
#include "NineGameInstance.h"
#include "WaveDurationRow.h"
#include "NinePlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"

ANineGameState::ANineGameState()
{
    PrimaryActorTick.bCanEverTick = true;

    SpawnedCoinCount = 0;
    CollectedCoinCount = 0;
    WaveDuration = 20.f;
    NumberOfWaves = 0;
    MaxLevelIndex = 0;
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

    SetWaveDuration();

    StartLevel();

    MaxLevelIndex = LevelNames.Num() - 1;
}

void ANineGameState::OnCoinCollected(int32 score)
{
    CollectedCoinCount++;
    GameInstance->AddTotalScore(score);

    UpdateHUD();

    if (SpawnedCoinCount <= CollectedCoinCount)
    {
        EndLevel();
    }
}

void ANineGameState::EndLevel()
{
    GameInstance->InitializeWaveIndex();
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

void ANineGameState::EndWave()
{
    GetWorldTimerManager().ClearTimer(LevelTimerHandle);
    GetWorldTimerManager().ClearTimer(HUDUpdateTimerHandle);

    GameInstance->IncreaseWaveIndex();
    if (GameInstance->GetCurrentWaveIndex() >= NumberOfWaves)
    {
        EndLevel();
    }
    else
    {
        if (LevelNames.IsValidIndex(GameInstance->GetCurrentLevelIndex()))
        {
            UGameplayStatics::OpenLevel(GetWorld(), LevelNames[GameInstance->GetCurrentLevelIndex()]);
        }
    }
}

void ANineGameState::SetWaveDuration()
{
    if (!WaveDurationTable) return;
    TArray<FWaveDurationRow*> AllRows;
    WaveDurationTable->GetAllRows(TEXT("WaveDurationContext"), AllRows);

    TArray<float> CurrentLevelRow = AllRows[GameInstance->GetCurrentLevelIndex()]->Duration;
    WaveDuration = CurrentLevelRow[GameInstance->GetCurrentWaveIndex()];
    UE_LOG(LogTemp, Warning, TEXT("Wave Duration Set to %.0f"), WaveDuration);

    NumberOfWaves = CurrentLevelRow.Num();
}

void ANineGameState::UpdateHUD() const
{
    if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
    {
        if (ANinePlayerController* NinePlayerController = Cast<ANinePlayerController>(PlayerController))
        {
            if (UUserWidget* HUD = NinePlayerController->GetHUDWidget())
            {
                if (UTextBlock* TimeText = Cast<UTextBlock>(HUD->GetWidgetFromName(TEXT("Time"))))
                {
                    float RemainingTime = GetWorldTimerManager().GetTimerRemaining(LevelTimerHandle);
                    TimeText->SetText(FText::FromString(FString::Printf(TEXT("Time: %.1f"), RemainingTime)));
                }

                if (UTextBlock* ScoreText = Cast<UTextBlock>(HUD->GetWidgetFromName(TEXT("Score"))))
                {
                    int32 Score = GameInstance->GetTotalScore();
                    ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), Score)));
                }

                if (UTextBlock* LevelText = Cast<UTextBlock>(HUD->GetWidgetFromName(TEXT("Level"))))
                {
                    int32 Level = GameInstance->GetCurrentLevelIndex() + 1;
                    LevelText->SetText(FText::FromString(FString::Printf(TEXT("Level: %d"), Level)));
                }
            }
        }
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

    if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
    {
        if (ANinePlayerController* NinePlayerController = Cast<ANinePlayerController>(PlayerController))
        {
            NinePlayerController->ShowGameHUD();
        }
    }

    GetWorldTimerManager().SetTimer(LevelTimerHandle, this, &ANineGameState::EndWave, WaveDuration, false);
    GetWorldTimerManager().SetTimer(HUDUpdateTimerHandle, this, &ANineGameState::UpdateHUD, 0.1f, true);
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
    if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
    {
        if (ANinePlayerController* NinePlayerController = Cast<ANinePlayerController>(PlayerController))
        {
            NinePlayerController->SetPause(true);
            NinePlayerController->ShowMainMenu(true);
        }
    }
}
