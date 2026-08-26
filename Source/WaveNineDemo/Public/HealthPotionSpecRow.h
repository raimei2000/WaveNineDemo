#pragma once

#include "CoreMinimal.h"
#include "HealthPotionSpecRow.generated.h"

USTRUCT(BlueprintType)
struct FHealthPotionSpecRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<float> HealAmountPerWave;
};
