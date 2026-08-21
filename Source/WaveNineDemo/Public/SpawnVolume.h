#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

class UBoxComponent;
class ABaseItem;
struct FItemSpawnRow;

UCLASS()
class WAVENINEDEMO_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnVolume();

	ABaseItem* RandomSpawnItem() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* SpawnVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnTable")
	UDataTable* ItemSpawnTable;

protected:
	virtual void BeginPlay() override;

	FVector GetRandomPointInVolume() const;

	FItemSpawnRow* GetRandomItem() const;

	ABaseItem* SpawnItem(TSubclassOf<ABaseItem> ItemClass) const;

private:
	FVector OriginLocation;
	float SizeX = 0.f;
	float SizeY = 0.f;
	float SizeZ = 0.f;
};
