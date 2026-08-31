#include "InteractWidget.h"

void UInteractWidget::OnHideAnimFinished()
{
    if (bHide)
    {
        SetVisibility(ESlateVisibility::Collapsed);
    }
}

void UInteractWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (ShowAnim)
    {
        FWidgetAnimationDynamicEvent EndDelegate;
        EndDelegate.BindDynamic(this, &UInteractWidget::OnHideAnimFinished);
        BindToAnimationFinished(ShowAnim, EndDelegate);
    }
    bHide = true;
    SetVisibility(ESlateVisibility::Collapsed);
}

void UInteractWidget::PlayShow()
{
    bHide = false;
    SetVisibility(ESlateVisibility::HitTestInvisible);
    if (ShowAnim)
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, FString::Printf(TEXT("SHOW@@")));
        PlayAnimation(ShowAnim, 0.f, 1, EUMGSequencePlayMode::Forward, 1.f);
    }
}

void UInteractWidget::PlayHide()
{
    bHide = true;
    if (ShowAnim)
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, FString::Printf(TEXT("Hide@@")));
        PlayAnimation(ShowAnim, 0.f, 1, EUMGSequencePlayMode::Reverse, 1.f);
    }
}
