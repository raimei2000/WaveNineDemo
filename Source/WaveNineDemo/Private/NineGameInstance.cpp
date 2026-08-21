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

int32 UNineGameInstance::GetTotalScore()
{
    return TotalScore;
}

int32 UNineGameInstance::GetCurrentLevelIndex()
{
    return CurrentLevelIndex;
}

void UNineGameInstance::IncreaseLevelIndex()
{
    CurrentLevelIndex++;
}
