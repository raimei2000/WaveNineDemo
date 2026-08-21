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

	void AddScore(int32 score);

protected:
	void StartLevel();

private:
	int32 Score;

	int32 SpawnedCoinCount;

	int32 CollectedCoinCount;

};
