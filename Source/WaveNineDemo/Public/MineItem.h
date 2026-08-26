#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "MineItem.generated.h"

class USphereComponent;

UCLASS()
class WAVENINEDEMO_API AMineItem : public ABaseItem
{
	GENERATED_BODY()

public:
	AMineItem();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Mine")
	float ExplosionDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Mine")
	float ExplosionRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Mine")
	float ExplosionDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effects")
	UParticleSystem* ExplosionParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effects")
	USoundBase* ExplosionSound;

	USphereComponent* ExplosionCollision;

	FTimerHandle ExplosionTimerHandle;

	bool bHasExploded;

public:
	virtual void ActivateItem(AActor* Activator) override;

	void Explode();

	void SetMineSpec(float Damage, float Delay);
};
