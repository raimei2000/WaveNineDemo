#pragma once

#include "CoreMinimal.h"
#include "BigCoinSpecRow.generated.h"

USTRUCT(BlueprintType)
struct FBigCoinSpecRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<int32> PointValuePerWave;
};
