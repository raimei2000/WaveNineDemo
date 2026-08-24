#include "NinePlayerController.h"
#include "NineGameState.h"
#include "NineGameInstance.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

ANinePlayerController::ANinePlayerController() :
    InputMappingContext(nullptr),
    MoveAction(nullptr),
    JumpAction(nullptr),
    LookAction(nullptr),
    SprintAction(nullptr),
    HUDWidgetInstance(nullptr),
    MainMenuWidgetInstance(nullptr)
{
}

UUserWidget* ANinePlayerController::GetHUDWidget() const
{
    return HUDWidgetInstance;
}

void ANinePlayerController::ShowGameHUD()
{
    if (HUDWidgetInstance)
    {
        HUDWidgetInstance->RemoveFromParent();
        HUDWidgetInstance = nullptr;
    }

    if (MainMenuWidgetInstance)
    {
        MainMenuWidgetInstance->RemoveFromParent();
        MainMenuWidgetInstance = nullptr;
    }

    if (HUDWidgetClass)
    {
        HUDWidgetInstance = CreateWidget<UUserWidget>(this, HUDWidgetClass);
        if (HUDWidgetInstance)
        {
            HUDWidgetInstance->AddToViewport();

            bShowMouseCursor = false;
            SetInputMode(FInputModeGameOnly());
        }

        if (ANineGameState* GameState = GetWorld() ? GetWorld()->GetGameState<ANineGameState>() : nullptr)
        {
            GameState->UpdateHUD();
        }
    }
}

void ANinePlayerController::ShowMainMenu(bool bIsRestart)
{
    if (HUDWidgetInstance)
    {
        HUDWidgetInstance->RemoveFromParent();
        HUDWidgetInstance = nullptr;
    }

    if (MainMenuWidgetInstance)
    {
        MainMenuWidgetInstance->RemoveFromParent();
        MainMenuWidgetInstance = nullptr;
    }

    if (MainMenuWidgetClass)
    {
        MainMenuWidgetInstance = CreateWidget<UUserWidget>(this, MainMenuWidgetClass);
        if (MainMenuWidgetInstance)
        {
            MainMenuWidgetInstance->AddToViewport();

            bShowMouseCursor = true;
            SetInputMode(FInputModeUIOnly());

            if (UTextBlock* ButtonText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName(TEXT("StartButtonText"))))
            {
                if (bIsRestart)
                {
                    ButtonText->SetText(FText::FromString(TEXT("Restart")));
                }
                else
                {
                    ButtonText->SetText(FText::FromString(TEXT("Start")));
                }
            }
        }
    }
}

void ANinePlayerController::StartGame()
{
    if (UNineGameInstance* NineGameInstance = Cast<UNineGameInstance>(UGameplayStatics::GetGameInstance(this)))
    {
        NineGameInstance->InitializeData();
    }

    UGameplayStatics::OpenLevel(GetWorld(), FName("BasicLevel"));
}

void ANinePlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
            LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
            if (InputMappingContext)
            {
                Subsystem->AddMappingContext(InputMappingContext, 0);
            }
        }
    }

    FString CurrentMapName = GetWorld()->GetMapName();
    if (CurrentMapName.Contains("MenuLevel"))
    {
        ShowMainMenu(false);
    }
}
