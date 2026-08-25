#pragma once

#include "CoreMinimal.h"
#include "SmallCoinSpecRow.generated.h"

USTRUCT(BlueprintType)
struct FSmallCoinSpecRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<int32> PointValuePerWave;
};
