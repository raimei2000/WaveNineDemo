#include "SmallCoinItem.h"

ASmallCoinItem::ASmallCoinItem()
{
    PointValue = 20;
    ItemType = "SmallCoin";
}

void ASmallCoinItem::ActivateItem(AActor* Activator)
{
    if (Activator && Activator->ActorHasTag("Player"))
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Small coin")));
        }
    }
}
