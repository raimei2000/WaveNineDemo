#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "MovableItem.generated.h"

UCLASS()
class WAVENINEDEMO_API AMovableItem : public ABaseItem
{
	GENERATED_BODY()

public:
	AMovableItem();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Motion")
	float RotationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Motion")
	float MaxRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Motion")
	float Period;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Motion", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float PhaseOffset = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Motion", meta = (ClampMin = "0.0", ClampMax = "90.0"))
	float RotationOffset = 0.f;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	void Move(float DeltaTime);

	void Rotate(float DeltaTime);

private:
	FVector StartLocation;
	FVector EndLocation;
	float RunningTime;
};
