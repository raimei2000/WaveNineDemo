#include "SlowItem.h"
#include "NineCharacter.h"

ASlowItem::ASlowItem()
{
    ItemType = "SlowItem";
}

void ASlowItem::ActivateItem(AActor* Activator)
{
    if (Activator && Activator->ActorHasTag("Player"))
    {
        Super::ActivateItem(Activator);

        if (ANineCharacter* Player = Cast<ANineCharacter>(Activator))
        {
            Player->ActivateSlow();
            Player->ActivateBlind();

            DestroyItem();
        }
    }
}
