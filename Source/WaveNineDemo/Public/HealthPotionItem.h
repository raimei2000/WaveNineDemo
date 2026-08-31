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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Heal")
	USphereComponent* NearSphere;

	virtual void ActivateItem(AActor* Activator) override;

	virtual void Tick(float DeltaTime) override;

	void UsePotion(AActor* Activator);

	UFUNCTION()
	virtual void NearOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void NearEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
};
