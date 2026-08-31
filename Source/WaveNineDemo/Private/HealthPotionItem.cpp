#include "HealthPotionItem.h"
#include "NineCharacter.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AHealthPotionItem::AHealthPotionItem()
{
    Tooltip = CreateDefaultSubobject<UWidgetComponent>(TEXT("Tooltip"));
    Tooltip->SetupAttachment(RootComponent);
    Tooltip->SetWidgetSpace(EWidgetSpace::Screen);

    HealAmount = 30.f;
    ItemType = "HealthPotion";
}

void AHealthPotionItem::SetHealthPotionSpec(float Amount)
{
    HealAmount = Amount;
}

void AHealthPotionItem::ActivateItem(AActor* Activator)
{
    Super::ActivateItem(Activator);

    if (Activator && Activator->ActorHasTag("Player"))
    {
        if (ANineCharacter* Player = Cast<ANineCharacter>(Activator))
        {
            Player->Heal(HealAmount);
        }
        DestroyItem();
    }
}

void AHealthPotionItem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!Tooltip->IsVisible())
    {
        return;
    }

    if (APlayerCameraManager* CamManager = UGameplayStatics::GetPlayerCameraManager(this, 0))
    {
        const FVector CameraLocation = CamManager->GetCameraLocation();
        const FVector WidgetLocation = Tooltip->GetComponentLocation();

        FRotator LookAt = UKismetMathLibrary::FindLookAtRotation(WidgetLocation, CameraLocation);
        LookAt.Pitch = 0.f;
        LookAt.Roll = 0.f;

        Tooltip->SetWorldRotation(LookAt);
    }
}
