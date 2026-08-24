#include "NineGameInstance.h"

UNineGameInstance::UNineGameInstance()
{
    TotalScore = 0;
    CurrentLevelIndex = 0;
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

void UNineGameInstance::IncreaseLevelIndex()
{
    CurrentLevelIndex++;
}

void UNineGameInstance::InitializeData()
{
    CurrentLevelIndex = 0;
    TotalScore = 0;
}
