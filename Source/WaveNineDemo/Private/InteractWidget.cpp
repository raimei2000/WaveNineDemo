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
}

void UInteractWidget::PlayShow()
{
    SetVisibility(ESlateVisibility::HitTestInvisible);

    if (ShowAnim)
    {
        bHide = false;
        PlayAnimation(ShowAnim, 0.f, 1, EUMGSequencePlayMode::Forward, 0.f);
    }
}

void UInteractWidget::PlayHide()
{
    if (ShowAnim)
    {
        bHide = true;
        PlayAnimation(ShowAnim, 0.f, 1, EUMGSequencePlayMode::Reverse, 0.f);
    }
}
