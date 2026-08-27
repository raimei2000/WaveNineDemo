#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trap.generated.h"

UCLASS()
class WAVENINEDEMO_API ATrap : public AActor
{
	GENERATED_BODY()
	
public:	
	ATrap();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trap|Components")
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trap|Components")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trap|Components")
	UDecalComponent* WarningDecal;

	UPROPERTY(EditAnywhere, Category = "Trap")
	float TriggerDelay;

	UPROPERTY(EditAnywhere, Category = "Trap")
	float AffectRadius;

	UPROPERTY(EditAnywhere, Category = "Trap")
	float Damage;

	FTimerHandle TriggerTimerHandle;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void TriggerTrap();

	virtual void DestroyTrap();
};
