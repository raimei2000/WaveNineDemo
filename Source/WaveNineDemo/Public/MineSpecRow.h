#pragma once

#include "CoreMinimal.h"
#include "MineSpecRow.generated.h"

USTRUCT(BlueprintType)
struct FMineSpecRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<float> DamagePerWave;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<float> ExplosionDelayPerWave;
};
