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

protected:
	UFUNCTION()
	virtual void OnFocused(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UFUNCTION()
	virtual void OnUnfocused(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	virtual void OnInteract(AActor* Activator) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Heal")
	float HealAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Heal")
	UWidgetComponent* Tooltip;

	virtual void ActivateItem(AActor* Activator) override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
};
