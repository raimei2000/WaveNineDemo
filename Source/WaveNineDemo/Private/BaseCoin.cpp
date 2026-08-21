#include "BaseCoin.h"
#include "NineGameState.h"
#include "Engine/World.h"

ABaseCoin::ABaseCoin()
{
    PointValue = 0;
    ItemType = "DefaultCoin";
}

void ABaseCoin::ActivateItem(AActor* Activator)
{
    if (Activator && Activator->ActorHasTag("Player"))
    {
        if (UWorld* World = GetWorld())
        {
            if (ANineGameState* GameState = World->GetGameState<ANineGameState>())
            {
                GameState->OnCoinCollected(PointValue);
            }
        }

        DestroyItem();
    }
}
