#pragma once

#include "CoreMinimal.h"
#include "WaveDurationRow.generated.h"

USTRUCT(BlueprintType)
struct FWaveDurationRow : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<float> Duration;
};
