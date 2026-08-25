#include "NineGameInstance.h"

UNineGameInstance::UNineGameInstance()
{
    TotalScore = 0;
    CurrentLevelIndex = 0;
    CurrentWaveIndex = 0;
}

void UNineGameInstance::AddTotalScore(int32 Amount)
{
    TotalScore += Amount;
}

int32 UNineGameInstance::GetTotalScore() const
{
    return TotalScore;
}

int32 UNineGameInstance::GetCurrentLevelIndex() const
{
    return CurrentLevelIndex;
}

int32 UNineGameInstance::GetCurrentWaveIndex() const
{
    return CurrentWaveIndex;
}

void UNineGameInstance::IncreaseLevelIndex()
{
    CurrentLevelIndex++;
}

void UNineGameInstance::InitializeData()
{
    CurrentLevelIndex = 0;
    TotalScore = 0;
    CurrentWaveIndex = 0;
}

void UNineGameInstance::IncreaseWaveIndex()
{
    CurrentWaveIndex++;
}

void UNineGameInstance::InitializeWaveIndex()
{
    CurrentWaveIndex = 0;
}
