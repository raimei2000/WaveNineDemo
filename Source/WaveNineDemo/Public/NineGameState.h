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

	void StartLevel();
};
