#include "BigCoinItem.h"

ABigCoinItem::ABigCoinItem()
{
    PointValue = 50;
    ItemType = "BigCoin";
}

void ABigCoinItem::ActivateItem(AActor* Activator)
{
    if (Activator && Activator->ActorHasTag("Player"))
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Big coin")));
        }
    }
}
