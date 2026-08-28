#pragma once

#include "CoreMinimal.h"
#include "Trap.h"
#include "Explosion.generated.h"

UCLASS()
class WAVENINEDEMO_API AExplosion : public ATrap
{
	GENERATED_BODY()

public:
	AExplosion();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap|Effects")
	UParticleSystem* PickupParticle;

	virtual void TriggerTrap() override;

	virtual void Affect(AActor* Hit) override;

	FTimerHandle DestroyParticleTimerHandle;

};
