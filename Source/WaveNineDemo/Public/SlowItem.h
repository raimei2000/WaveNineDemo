#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "SlowItem.generated.h"

UCLASS()
class WAVENINEDEMO_API ASlowItem : public ABaseItem
{
	GENERATED_BODY()

public:
	ASlowItem();

protected:
	virtual void ActivateItem(AActor* Activator) override;
};
