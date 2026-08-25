#pragma once

#include "CoreMinimal.h"
#include "FloatArrayRow.generated.h"

USTRUCT(BlueprintType)
struct FFloatArrayRow
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grid")
	TArray<float> RowValues;

	float& operator[](int32 Index);
	const float& operator[](int32 Index) const;
};
