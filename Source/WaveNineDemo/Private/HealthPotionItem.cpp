#include "HealthPotionItem.h"
#include "NineCharacter.h"
#include "InteractWidget.h"
#include "Components/WidgetComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AHealthPotionItem::AHealthPotionItem()
{
    Tooltip = CreateDefaultSubobject<UWidgetComponent>(TEXT("Tooltip"));
    Tooltip->SetupAttachment(RootComponent);
    Tooltip->SetWidgetSpace(EWidgetSpace::World);

    Collision->OnComponentBeginOverlap.RemoveAll(this);
    Collision->OnComponentEndOverlap.RemoveAll(this);

    HealAmount = 30.f;
    ItemType = "HealthPotion";
}

void AHealthPotionItem::SetHealthPotionSpec(float Amount)
{
    HealAmount = Amount;
}

void AHealthPotionItem::OnFocused_Implementation()
{
    if (UInteractWidget* WidgetInstance = Cast<UInteractWidget>(Tooltip->GetUserWidgetObject()))
    {
        WidgetInstance->PlayShow();
    }
}

void AHealthPotionItem::OnUnfocused_Implementation()
{
    if (UInteractWidget* WidgetInstance = Cast<UInteractWidget>(Tooltip->GetUserWidgetObject()))
    {
        WidgetInstance->PlayHide();
    }
}

void AHealthPotionItem::OnInteract_Implementation(AActor* Interactor)
{
    ActivateItem(Interactor);
}

bool AHealthPotionItem::CanInteract_Implementation() const
{
    return true;
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

void AHealthPotionItem::BeginPlay()
{
    Super::BeginPlay();
    Tooltip->InitWidget();
}

void AHealthPotionItem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    UUserWidget* W = Tooltip->GetUserWidgetObject();
    if (!W || W->GetVisibility() == ESlateVisibility::Collapsed)
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
