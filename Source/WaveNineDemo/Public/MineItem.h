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

	USphereComponent* ExplosionCollision;

	FTimerHandle ExplosionTimerHandle;

public:
	virtual void ActivateItem(AActor* Activator) override;

	void Explode();
};
