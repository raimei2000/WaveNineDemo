#include "HealthPotionItem.h"

AHealthPotionItem::AHealthPotionItem()
{
    HealAmount = 30.f;
    ItemType = "HealthPotion";
}

void AHealthPotionItem::ActivateItem(AActor* Activator)
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString(TEXT("Heal")));
    }
}
