#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "NineGameInstance.generated.h"

UCLASS()
class WAVENINEDEMO_API UNineGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UNineGameInstance();

	UFUNCTION(BlueprintCallable)
	int32 GetTotalScore() const;

	UFUNCTION(BlueprintCallable)
	int32 GetCurrentLevelIndex() const;

	void AddTotalScore(int32 Amount);

	void IncreaseLevelIndex();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameDate")
	int32 TotalScore;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameDate")
	int32 CurrentLevelIndex;
};
