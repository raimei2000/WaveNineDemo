#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "NineGameInstance.generated.h"

UCLASS()
class WAVENINEDEMO_API UNineGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UNineGameInstance();

	void AddTotalScore(int32 Amount);

	int32 GetTotalScore();

	int32 GetCurrentLevelIndex();

	void IncreaseLevelIndex();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameDate")
	int32 TotalScore;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameDate")
	int32 CurrentLevelIndex;
};
