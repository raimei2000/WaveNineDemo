#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "MovableItem.h"
#include "HealthPotionItem.generated.h"

class UWidgetComponent;

UCLASS()
class WAVENINEDEMO_API AHealthPotionItem : public AMovableItem, public IInteractable
{
	GENERATED_BODY()

public:
	AHealthPotionItem();

	void SetHealthPotionSpec(float Amount);

	virtual void OnFocused_Implementation() override;

	virtual void OnUnfocused_Implementation() override;

	virtual void OnInteract_Implementation(AActor* Interactor) override;

	virtual bool CanInteract_Implementation() const override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Heal")
	float HealAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Heal")
	UWidgetComponent* Tooltip;

	virtual void ActivateItem(AActor* Activator) override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
};
