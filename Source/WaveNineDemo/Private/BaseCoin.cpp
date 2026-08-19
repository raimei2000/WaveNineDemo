#include "BaseCoin.h"

ABaseCoin::ABaseCoin()
{
    PrimaryActorTick.bCanEverTick = true;

    PointValue = 0;
    ItemType = "DefaultCoin";
}

void ABaseCoin::ActivateItem(AActor* Activator)
{
    if (Activator && Activator->ActorHasTag("Player"))
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, FString::Printf(TEXT("Coin")));
        DestroyItem();
    }
}
