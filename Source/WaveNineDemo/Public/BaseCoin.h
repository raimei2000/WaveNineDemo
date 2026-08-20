#pragma once

#include "CoreMinimal.h"
#include "MovableItem.h"
#include "BaseCoin.generated.h"

UCLASS()
class WAVENINEDEMO_API ABaseCoin : public AMovableItem
{
	GENERATED_BODY()

public:
	ABaseCoin();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 PointValue;

	virtual void ActivateItem(AActor* Activator) override;
};
