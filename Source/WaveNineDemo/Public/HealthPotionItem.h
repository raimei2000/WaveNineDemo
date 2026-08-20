#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "HealthPotionItem.generated.h"

UCLASS()
class WAVENINEDEMO_API AHealthPotionItem : public ABaseItem
{
	GENERATED_BODY()

public:
	AHealthPotionItem();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Heal")
	float HealAmount;

	virtual void ActivateItem(AActor* Activator) override;
	
};
