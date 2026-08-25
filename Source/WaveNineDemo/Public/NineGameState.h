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

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game|Data")
	UDataTable* WaveDurationTable;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game|Levels")
	TArray<FName> LevelNames;

protected:
	void StartLevel();

	virtual void Tick(float DeltaTime) override;

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
