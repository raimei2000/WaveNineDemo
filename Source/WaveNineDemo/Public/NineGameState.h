#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "NineGameState.generated.h"

UCLASS()
class WAVENINEDEMO_API ANineGameState : public AGameState
{
	GENERATED_BODY()

public:
	ANineGameState();

	virtual void BeginPlay() override;

	void OnCoinCollected(int32 score);

protected:
	void StartLevel();

	virtual void Tick(float DeltaTime) override;

private:
	void AddScore(int32 score);

	void EndLevel();

private:
	int32 Score;

	int32 SpawnedCoinCount;

	int32 CollectedCoinCount;

};
