#pragma once

#include "CoreMinimal.h"
#include "Trap.h"
#include "SpikeTrap.generated.h"

UCLASS()
class WAVENINEDEMO_API ASpikeTrap : public ATrap
{
	GENERATED_BODY()

public:
	ASpikeTrap();

	virtual void BeginPlay() override;

protected:
	virtual void TriggerTrap() override;

	FTimerHandle DestroyTimerHandle;

	float DestroyDelay;
};
