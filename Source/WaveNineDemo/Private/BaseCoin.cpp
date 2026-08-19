// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCoin.h"

ABaseCoin::ABaseCoin()
{
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
