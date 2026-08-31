#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractWidget.generated.h"

UCLASS()
class WAVENINEDEMO_API UInteractWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> ShowAnim;

	UFUNCTION()
	void OnHideAnimFinished();

	virtual void NativeConstruct() override;

	void PlayShow();

	void PlayHide();

private:
	bool bHide;
};
