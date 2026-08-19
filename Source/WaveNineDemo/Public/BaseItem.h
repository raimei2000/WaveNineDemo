#pragma once

#include "CoreMinimal.h"
#include "ItemInterface.h"
#include "GameFramework/Actor.h"
#include "BaseItem.generated.h"

class USphereComponent;

UCLASS()
class WAVENINEDEMO_API ABaseItem : public AActor, public IItemInterface
{
	GENERATED_BODY()
	
public:	
	ABaseItem();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName ItemType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	USphereComponent* Collision;

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
	UFUNCTION()
	virtual void OnItemOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) override;

	UFUNCTION()
	virtual void OnItemEndOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) override;

	virtual void ActivateItem(AActor* Activator) override;

	virtual FName GetItemType() const override;

	virtual void DestroyItem();

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
