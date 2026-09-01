#include "NineGameState.h"
#include "SpawnVolume.h"
#include "SpawnBoard.h"
#include "BaseItem.h"
#include "BaseCoin.h"
#include "BigCoinItem.h"
#include "SmallCoinItem.h"
#include "HealthPotionItem.h"
#include "MineItem.h"
#include "NineGameInstance.h"
#include "WaveDurationRow.h"
#include "BigCoinSpecRow.h"
#include "SmallCoinSpecRow.h"
#include "HealthPotionSpecRow.h"
#include "MineSpecRow.h"
#include "NinePlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"

ANineGameState::ANineGameState()
{
    PrimaryActorTick.bCanEverTick = false;

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
        EndWave();
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
    const FName RowName = *FString::Printf(TEXT("Level%d"), GameInstance->GetCurrentLevelIndex() + 1);
    FWaveDurationRow* CurrentLevelRow = WaveDurationTable->FindRow<FWaveDurationRow>(RowName, TEXT("WaveDuration"));
    WaveDuration = CurrentLevelRow->Duration[GameInstance->GetCurrentWaveIndex()];
    NumberOfWaves = CurrentLevelRow->Duration.Num();
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
                    TimeText->SetText(FText::FromString(FString::Printf(TEXT("%.1f"), RemainingTime)));
                }

                if (UTextBlock* ScoreText = Cast<UTextBlock>(HUD->GetWidgetFromName(TEXT("Score"))))
                {
                    int32 Score = GameInstance->GetTotalScore();
                    ScoreText->SetText(FText::FromString(FString::Printf(TEXT("%d"), Score)));
                }

                if (UTextBlock* LevelText = Cast<UTextBlock>(HUD->GetWidgetFromName(TEXT("Level"))))
                {
                    int32 Level = GameInstance->GetCurrentLevelIndex() + 1;
                    int32 Wave = GameInstance->GetCurrentWaveIndex() + 1;
                    LevelText->SetText(FText::FromString(FString::Printf(TEXT("%d-%d"), Level, Wave)));
                }

                if (UTextBlock* CollectedCoinText = Cast<UTextBlock>(HUD->GetWidgetFromName(TEXT("CollectedCoin"))))
                {
                    CollectedCoinText->SetText(FText::FromString(FString::Printf(TEXT("%d"), CollectedCoinCount)));
                }

                if (UTextBlock* SpawnedCoinText = Cast<UTextBlock>(HUD->GetWidgetFromName(TEXT("SpawnedCoin"))))
                {
                    SpawnedCoinText->SetText(FText::FromString(FString::Printf(TEXT("%d"), SpawnedCoinCount)));
                }
            }
        }
    }
}

void ANineGameState::StartLevel()
{
    TArray<AActor*> Volumes;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), Volumes);

    const int32 LevelIndex = GameInstance->GetCurrentLevelIndex();
    const int32 WaveIndex = GameInstance->GetCurrentWaveIndex();

    const FName RowName = *FString::Printf(TEXT("Level%d"), LevelIndex + 1);
    const FBigCoinSpecRow* BigCoinRow = BigCoinSpecTable->FindRow<FBigCoinSpecRow>(RowName, TEXT("BigCoinSpec"));
    const FSmallCoinSpecRow* SmallCoinRow = SmallCoinSpecTable->FindRow<FSmallCoinSpecRow>(RowName, TEXT("SmallCoinSpec"));
    const FHealthPotionSpecRow* HealthPotionRow = HealthPotionSpecTable->FindRow<FHealthPotionSpecRow>(RowName, TEXT("HealthPotionSpec"));
    const FMineSpecRow* MineRow = MineSpecTable->FindRow<FMineSpecRow>(RowName, TEXT("MineSpec"));

    // Spawn Items
    if (Volumes.Num() > 0) {
        const int32 ItemToSpawn = 40;

        for (int32 i = 0; i < ItemToSpawn; i++)
        {
            if (ASpawnVolume* Volume = Cast<ASpawnVolume>(Volumes[0]))
            {
                ABaseItem* SpawnedItem = Volume->RandomSpawnItem(LevelIndex, WaveIndex);
                if (SpawnedItem && SpawnedItem->IsA(ABaseCoin::StaticClass()))
                {
                    SpawnedCoinCount++;
                }

                // Level, Wave별 아이템 능력치 설정
                if (SpawnedItem && SpawnedItem->IsA(ABigCoinItem::StaticClass()))
                {
                    ABaseCoin* BigCoin = Cast<ABaseCoin>(SpawnedItem);
                    BigCoin->SetCoinSpec(BigCoinRow->PointValuePerWave[WaveIndex]);
                }
                if (SpawnedItem && SpawnedItem->IsA(ASmallCoinItem::StaticClass()))
                {
                    ABaseCoin* SmallCoin = Cast<ABaseCoin>(SpawnedItem);
                    SmallCoin->SetCoinSpec(SmallCoinRow->PointValuePerWave[WaveIndex]);
                }
                if (SpawnedItem && SpawnedItem->IsA(AHealthPotionItem::StaticClass()))
                {
                    AHealthPotionItem* HealthPotion = Cast<AHealthPotionItem>(SpawnedItem);
                    HealthPotion->SetHealthPotionSpec(HealthPotionRow->HealAmountPerWave[WaveIndex]);
                }
                if (SpawnedItem && SpawnedItem->IsA(AMineItem::StaticClass()))
                {
                    AMineItem* Mine = Cast<AMineItem>(SpawnedItem);
                    Mine->SetMineSpec(MineRow->DamagePerWave[WaveIndex], MineRow->ExplosionDelayPerWave[WaveIndex]);
                }
            }
        }
    }

    // Activate Traps
    if (WaveIndex >= 1) {
        TArray<AActor*> Boards;
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnBoard::StaticClass(), Boards);

        if (Boards.Num() > 0)
        {
            for (AActor* Actor : Boards)
            {
                if (ASpawnBoard* Board = Cast<ASpawnBoard>(Actor))
                {
                    if (Board->GetTrapName() == FName("Explosion")) // Explosion trap
                    {
                        if (WaveIndex >= 2)
                        {
                            Board->Activate(220.f);
                        }
                    }
                    else                                            // Spike trap
                    {
                        Board->Activate(-12.f);
                    }
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

void ANineGameState::CheatEndWave()
{
    EndWave();
}
