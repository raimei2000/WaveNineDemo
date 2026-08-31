#pragma once

#include "CoreMinimal.h"
#include "MovableItem.h"
#include "HealthPotionItem.generated.h"

class UWidgetComponent;

UCLASS()
class WAVENINEDEMO_API AHealthPotionItem : public AMovableItem
{
	GENERATED_BODY()

public:
	AHealthPotionItem();

	void SetHealthPotionSpec(float Amount);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Heal")
	float HealAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Heal")
	UWidgetComponent* Tooltip;

	virtual void ActivateItem(AActor* Activator) override;

	virtual void Tick(float DeltaTime) override;
	
};
