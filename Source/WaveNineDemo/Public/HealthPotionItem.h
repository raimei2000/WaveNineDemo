#pragma once

#include "CoreMinimal.h"
#include "MovableItem.h"
#include "HealthPotionItem.generated.h"

UCLASS()
class WAVENINEDEMO_API AHealthPotionItem : public AMovableItem
{
	GENERATED_BODY()

public:
	AHealthPotionItem();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Heal")
	float HealAmount;

	virtual void ActivateItem(AActor* Activator) override;
	
};
