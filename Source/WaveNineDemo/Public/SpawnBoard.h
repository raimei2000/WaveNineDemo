#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnBoard.generated.h"

class UBoxComponent;
class ATrap;

UCLASS()
class WAVENINEDEMO_API ASpawnBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnBoard();

	void Activate();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* SpawnBoard;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn")
	TSubclassOf<ATrap> ActorToSpawn;

private:
	FVector2D GetRandomPointOnBoard() const;

	void SpawnTrap() const;

private:
	FVector OriginLocation;
	float SizeX = 0.f;
	float SizeY = 0.f;

	FTimerHandle SpawnSpikeTimerHandle;
	float SpawnDelay;
};
