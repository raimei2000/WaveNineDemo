#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

class UBoxComponent;
UCLASS()
class WAVENINEDEMO_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnVolume();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* SpawnVolume;

protected:
	virtual void BeginPlay() override;

	FVector GetRandomPointInVolume();

private:
	FVector OriginLocation;
	float SizeX = 0.f;
	float SizeY = 0.f;
	float SizeZ = 0.f;
};
