#include "SpikeTrap.h"
#include "NineCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

ASpikeTrap::ASpikeTrap()
{
    TriggerDelay = 3.f;
    AffectRadius = 130.f;
    Damage = 20.f;
}

void ASpikeTrap::TriggerTrap()
{
    Super::TriggerTrap();

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
