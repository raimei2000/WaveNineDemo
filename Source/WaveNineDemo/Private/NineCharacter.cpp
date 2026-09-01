#include "NineCharacter.h"
#include "WaveNineDemo/WaveNineDemo.h"
#include "NinePlayerController.h"
#include "NineGameState.h"
#include "HealthPotionItem.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/VerticalBox.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

ANineCharacter::ANineCharacter()
{
    PrimaryActorTick.bCanEverTick = false;

    DefaultSpringArmLength = 300.f;
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->TargetArmLength = DefaultSpringArmLength;
    SpringArm->bUsePawnControlRotation = true;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm , USpringArmComponent::SocketName);
    Camera->bUsePawnControlRotation = false;

    NormalSpeed = 600.0f;
    CurrentSpeed = NormalSpeed;
    SprintSpeedMultiplier = 1.7f;
    SprintSpeed = NormalSpeed * SprintSpeedMultiplier;

    SlowDuration = 2.5f;
    SlowFactor = 0.7f;
    MaxSlowStack = 3;
    SlowStack = 0;
    bSlow = false;

    BlindDuration = 3.f;
    bBlind = false;
    DebuffSpringArmLength = 100.f;

    ConfusionDuration = 3.f;
    ConfusedDirection = 1.f;
    bConfusion = false;

    GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;

    MaxHealth = 100;
    Health = MaxHealth;
}

void ANineCharacter::Move(const FInputActionValue& Value)
{
    if (!Controller) return; // controller 유효성 검사

    const FVector2D MoveInput = Value.Get<FVector2D>();

    if (!FMath::IsNearlyZero(MoveInput.X))
    {
        AddMovementInput(ConfusedDirection * GetActorForwardVector(), MoveInput.X);
    }
    if (!FMath::IsNearlyZero(MoveInput.Y))
    {
        AddMovementInput(ConfusedDirection * GetActorRightVector(), MoveInput.Y);
    }
}

void ANineCharacter::StartJump(const FInputActionValue& Value)
{
    if (Value.Get<bool>())
    {
        Jump();
    }
}

void ANineCharacter::StopJump(const FInputActionValue& Value)
{
    if (!Value.Get<bool>())
    {
        StopJumping();
    }
}

void ANineCharacter::Look(const FInputActionValue& Value)
{
    FVector2D LookInput = Value.Get<FVector2D>();
    AddControllerYawInput(LookInput.X);
    AddControllerPitchInput(LookInput.Y);
}

void ANineCharacter::StartSprint(const FInputActionValue& Value)
{
    if (bSlow) return;
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->MaxWalkSpeed = CurrentSpeed * SprintSpeedMultiplier;
    }
}

void ANineCharacter::StopSprint(const FInputActionValue& Value)
{
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->MaxWalkSpeed = CurrentSpeed;
    }
}

void ANineCharacter::Interact(const FInputActionValue& Value)
{
    if (FocusedActor && FocusedActor->Implements<UInteractable>())
    {
        IInteractable::Execute_OnInteract(FocusedActor, this);
    }
}

float ANineCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
    Health = FMath::Clamp(Health - DamageAmount, 0.f, MaxHealth);
    UpdateHPUI();

    if (Health <= 0.f)
    {
        OnDeath();
    }
    return ActualDamage;
}

void ANineCharacter::UpdateHPUI()
{
    if (ANinePlayerController* NinePlayerController = Cast<ANinePlayerController>(GetController()))
    {
        if (UUserWidget* HUD = NinePlayerController->GetHUDWidget())
        {
            if (UProgressBar* HPBar = Cast<UProgressBar>(HUD->GetWidgetFromName(TEXT("HPBar"))))
            {
                HPBar->SetPercent(Health / MaxHealth);
            }
            if (UTextBlock* HPPercent = Cast<UTextBlock>(HUD->GetWidgetFromName(TEXT("HPPercent"))))
            {
                HPPercent->SetText(FText::FromString(FString::Printf(TEXT("%.0f%%"), Health)));
            }
        }
    }
}

void ANineCharacter::UpdateDebuffUI()
{
    if (ANinePlayerController* NinePlayerController = Cast<ANinePlayerController>(GetController()))
    {
        if (UUserWidget* HUD = NinePlayerController->GetHUDWidget())
        {
            if (UVerticalBox* SlowBox = Cast<UVerticalBox>(HUD->GetWidgetFromName(TEXT("SlowVerticalBox"))))
            {
                if (bSlow)
                {
                    if (UTextBlock* SlowStackText = Cast<UTextBlock>(HUD->GetWidgetFromName(TEXT("SlowStack"))))
                    {
                        SlowStackText->SetText(FText::FromString(FString::Printf(TEXT("x%d"), SlowStack)));
                    }
                    SlowBox->SetVisibility(ESlateVisibility::HitTestInvisible);
                }
                else
                {

                    SlowBox->SetVisibility(ESlateVisibility::Collapsed);
                }
            }

            if (UWidget* ConfusionText = HUD->GetWidgetFromName(TEXT("ConfusionText")))
            {
                if (bConfusion)
                {
                    ConfusionText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
                }
                else
                {
                    ConfusionText->SetVisibility(ESlateVisibility::Collapsed);
                }
            }

            if (UWidget* BlindImage = HUD->GetWidgetFromName(TEXT("BlindImage")))
            {
                if (bBlind)
                {
                    BlindImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
                }
                else
                {
                    BlindImage->SetVisibility(ESlateVisibility::Hidden);
                }
            }
        }
    }
}

void ANineCharacter::BeginPlay()
{
    Super::BeginPlay();
    UpdateHPUI();

    CosLimit = FMath::Cos(FMath::DegreesToRadians(InteractHalfAngle));
    GetWorldTimerManager().SetTimer(ScanTimerHandle, this, &ANineCharacter::ScanForInteractable, ScanInterval, true);
}

void ANineCharacter::ScanForInteractable()
{
    AActor* NewFocus = FindBestInteractable();

    if (NewFocus == FocusedActor)
    {
        return;
    }

    if (FocusedActor)
    {
        IInteractable::Execute_OnUnfocused(FocusedActor);
    }

    if (NewFocus)
    {
        IInteractable::Execute_OnFocused(NewFocus);
    }

    FocusedActor = NewFocus;
}

AActor* ANineCharacter::FindBestInteractable() const
{
    TArray<AActor*> Overlapped;

    TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
    ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Interactable));

    TArray<AActor*> IgnoreActors;
    IgnoreActors.Add(const_cast<ANineCharacter*>(this));

    UKismetSystemLibrary::SphereOverlapActors(
        GetWorld(), GetActorLocation(), InteractionRadius,
        ObjectTypes, nullptr, IgnoreActors, Overlapped);

    FVector ViewDirection = GetActorForwardVector();
    if (const APlayerCameraManager* CamMgr = UGameplayStatics::GetPlayerCameraManager(this, 0))
    {
        ViewDirection = CamMgr->GetCameraRotation().Vector();
    }

    AActor* Best = nullptr;
    float BestScore = -1.f;

    for (AActor* Candidate : Overlapped)
    {
        if (!Candidate || !Candidate->Implements<UInteractable>())
        {
            continue;
        }

        if (!IInteractable::Execute_CanInteract(Candidate))
        {
            continue;
        }

        const FVector ToTarget = Candidate->GetActorLocation() - GetActorLocation();
        const float Distance = ToTarget.Size();
        if (Distance < KINDA_SMALL_NUMBER)
        {
            continue; // 너무 가까이 있다면 제외
        }

        const float Dot = FVector::DotProduct(ViewDirection, ToTarget / Distance);
        if (Dot < CosLimit)
        {
            continue; // 시야각 밖에 있다면 제외
        }

        const float Score = Dot * (1.f - Distance / InteractionRadius);
        if (Score > BestScore)
        {
            Best = Candidate;
            BestScore = Score;
        }
    }
    return Best;
}

float ANineCharacter::GetCharacterHealth() const
{
    return Health;
}

void ANineCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        if (ANinePlayerController* PlayerController = Cast<ANinePlayerController>(GetController()))
        {
            if (PlayerController->MoveAction)
            {
                EnhancedInput->BindAction(PlayerController->MoveAction,
                                          ETriggerEvent::Triggered,
                                          this,
                                          &ANineCharacter::Move);
            }
            if (PlayerController->LookAction)
            {
                EnhancedInput->BindAction(PlayerController->LookAction,
                                          ETriggerEvent::Triggered,
                                          this,
                                          &ANineCharacter::Look);
            }
            if (PlayerController->JumpAction)
            {
                EnhancedInput->BindAction(PlayerController->JumpAction,
                                          ETriggerEvent::Triggered,
                                          this,
                                          &ANineCharacter::StartJump);
                EnhancedInput->BindAction(PlayerController->JumpAction,
                                          ETriggerEvent::Completed,
                                          this,
                                          &ANineCharacter::StopJump);
            }
            if (PlayerController->SprintAction)
            {
                EnhancedInput->BindAction(PlayerController->SprintAction,
                                          ETriggerEvent::Triggered,
                                          this,
                                          &ANineCharacter::StartSprint);
                EnhancedInput->BindAction(PlayerController->SprintAction,
                                          ETriggerEvent::Completed,
                                          this,
                                          &ANineCharacter::StopSprint);
            }
            if (PlayerController->InterAction)
            {
                EnhancedInput->BindAction(PlayerController->InterAction,
                                          ETriggerEvent::Started,
                                          this,
                                          &ANineCharacter::Interact);
            }
        }
    }
}

void ANineCharacter::Heal(float HealAmount)
{
    Health = FMath::Clamp(Health + HealAmount, 0.f, MaxHealth);
    UpdateHPUI();
}

void ANineCharacter::ActivateSlow()
{
    GetWorldTimerManager().ClearTimer(SlowTimerHandle);
    GetWorldTimerManager().SetTimer(SlowTimerHandle, this, &ANineCharacter::DeactivateSlow, SlowDuration, false);

    if (SlowStack >= MaxSlowStack) return;

    CurrentSpeed *= SlowFactor;
    GetCharacterMovement()->MaxWalkSpeed = CurrentSpeed;

    bSlow = true;
    SlowStack++;

    UpdateDebuffUI();
}

void ANineCharacter::DeactivateSlow()
{
    CurrentSpeed = NormalSpeed;
    GetCharacterMovement()->MaxWalkSpeed = CurrentSpeed;

    bSlow = false;
    SlowStack = 0;

    UpdateDebuffUI();
}

void ANineCharacter::ActivateBlind()
{
    GetWorldTimerManager().ClearTimer(BlindTimerHandle);
    GetWorldTimerManager().SetTimer(BlindTimerHandle, this, &ANineCharacter::DeactivateBlind, BlindDuration, false);

    SpringArm->TargetArmLength = DebuffSpringArmLength;
    bBlind = true;

    UpdateDebuffUI();
}

void ANineCharacter::DeactivateBlind()
{
    SpringArm->TargetArmLength = DefaultSpringArmLength;
    bBlind = false;

    UpdateDebuffUI();
}

void ANineCharacter::ActivateConfuse()
{
    GetWorldTimerManager().ClearTimer(ConfusionTimerHandle);
    GetWorldTimerManager().SetTimer(ConfusionTimerHandle, this, &ANineCharacter::DeactivateConfuse, ConfusionDuration, false);

    ConfusedDirection = -1.f;
    bConfusion = true;

    UpdateDebuffUI();
}

void ANineCharacter::DeactivateConfuse()
{
    ConfusedDirection = 1.f;
    bConfusion = false;

    UpdateDebuffUI();
}

void ANineCharacter::OnDeath()
{
    ANineGameState* NineGameState = GetWorld()->GetGameState<ANineGameState>();
    if (NineGameState)
    {
        NineGameState->OnGameOver();
    }
}
