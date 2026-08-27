#include "SpikeTrap.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"

ASpikeTrap::ASpikeTrap()
{
    TriggerDelay = 3.f;
    AffectRadius = 155.f;
    Damage = 20.f;
    DestroyDelay = 0.5f;

    WarningDecal->DecalSize = FVector(100.f, AffectRadius, AffectRadius);
    WarningDecal->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
}

void ASpikeTrap::BeginPlay()
{
    Super::BeginPlay();

    StaticMesh->SetVisibility(false);
}

void ASpikeTrap::TriggerTrap()
{
    Super::TriggerTrap();

    StaticMesh->SetVisibility(true);
    WarningDecal->SetVisibility(false);

    GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &ASpikeTrap::DestroyTrap, DestroyDelay, false);
}
