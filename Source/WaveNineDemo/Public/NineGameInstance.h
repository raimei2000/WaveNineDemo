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

	UFUNCTION(BlueprintCallable)
	int32 GetTotalScore() const;

	UFUNCTION(BlueprintCallable)
	int32 GetCurrentLevelIndex() const;

	UFUNCTION(BlueprintCallable)
	int32 GetCurrentWaveIndex() const;

	void AddTotalScore(int32 Amount);

	void IncreaseLevelIndex();

	void InitializeData();

	void IncreaseWaveIndex();

	void InitializeWaveIndex();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameData")
	int32 TotalScore;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameData")
	int32 CurrentLevelIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameData")
	int32 CurrentWaveIndex;
};
