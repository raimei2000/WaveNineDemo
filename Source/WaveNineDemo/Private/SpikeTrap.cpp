#include "SpikeTrap.h"
#include "NineCharacter.h"
#include "Components/DecalComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

ASpikeTrap::ASpikeTrap()
{
    TriggerDelay = 3.f;
    AffectRadius = 130.f;
    Damage = 20.f;

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

    TArray<AActor*> Hits;
    TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
    ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

    UKismetSystemLibrary::SphereOverlapActors(
        this, GetActorLocation(), AffectRadius,
        ObjectTypes, ANineCharacter::StaticClass(), TArray<AActor*> {this}, Hits);

    for (AActor* Hit : Hits)
    {
        UGameplayStatics::ApplyDamage(Hit, Damage, nullptr, this, UDamageType::StaticClass());
    }
}
