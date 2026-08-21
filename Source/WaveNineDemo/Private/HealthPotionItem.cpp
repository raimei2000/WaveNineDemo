#include "HealthPotionItem.h"
#include "NineCharacter.h"

AHealthPotionItem::AHealthPotionItem()
{
    HealAmount = 30.f;
    ItemType = "HealthPotion";
}

void AHealthPotionItem::ActivateItem(AActor* Activator)
{
    if (Activator && Activator->ActorHasTag("Player"))
    {
        if (ANineCharacter* Player = Cast<ANineCharacter>(Activator))
        {
            Player->Heal(HealAmount);
        }
        DestroyItem();
    }
}
