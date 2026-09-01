#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "NineGameState.generated.h"

class UNineGameInstance;

UCLASS()
class WAVENINEDEMO_API ANineGameState : public AGameState
{
	GENERATED_BODY()

public:
	ANineGameState();

	virtual void BeginPlay() override;

	void OnCoinCollected(int32 score);

	void UpdateHUD() const;

	void OnGameOver();

	void CheatEndWave();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game|Data")
	UDataTable* WaveDurationTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game|Data")
	UDataTable* BigCoinSpecTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game|Data")
	UDataTable* SmallCoinSpecTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game|Data")
	UDataTable* HealthPotionSpecTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game|Data")
	UDataTable* MineSpecTable;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game|Levels")
	TArray<FName> LevelNames;

protected:
	void StartLevel();

private:
	void EndLevel();

	void EndWave();

	void SetWaveDuration();

private:
	int32 SpawnedCoinCount;

	int32 CollectedCoinCount;

	FTimerHandle LevelTimerHandle;

	FTimerHandle HUDUpdateTimerHandle;

	float WaveDuration;

	int32 MaxLevelIndex;

	int32 NumberOfWaves;

	UNineGameInstance* GameInstance;
};
