#pragma once

#include "CoreMinimal.h"
#include "BaseCoin.h"
#include "SmallCoinItem.generated.h"

UCLASS()
class WAVENINEDEMO_API ASmallCoinItem : public ABaseCoin
{
	GENERATED_BODY()

public:
	ASmallCoinItem();

	virtual void ActivateItem(AActor* Activator) override;
	
};
