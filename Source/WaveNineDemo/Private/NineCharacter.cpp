#include "NineCharacter.h"
#include "NinePlayerController.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ANineCharacter::ANineCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->TargetArmLength = 300.0f;
    SpringArm->bUsePawnControlRotation = true;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm , USpringArmComponent::SocketName);
    Camera->bUsePawnControlRotation = false;

    NormalSpeed = 600.0f;
    SprintSpeedMultiplier = 1.7f;
    SprintSpeed = NormalSpeed * SprintSpeedMultiplier;

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
        AddMovementInput(GetActorForwardVector(), MoveInput.X);
    }
    if (!FMath::IsNearlyZero(MoveInput.Y))
    {
        AddMovementInput(GetActorRightVector(), MoveInput.Y);
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
    FVector2D LookInput = Value.Get<FVector2d>();
    AddControllerYawInput(LookInput.X);
    AddControllerPitchInput(LookInput.Y);
}

void ANineCharacter::StartSprint(const FInputActionValue& Value)
{
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
    }
}

void ANineCharacter::StopSprint(const FInputActionValue& Value)
{
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
    }
}

float ANineCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
    Health = FMath::Clamp(Health - DamageAmount, 0.f, MaxHealth);

    if (Health <= 0.f)
    {
        //Death
    }
    return ActualDamage;
}

void ANineCharacter::Tick(float DeltaTime)
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(2, 0.f, FColor::Red, FString::Printf(TEXT("Player HP: %.0f"), Health));
    }
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
        }
    }

}

void ANineCharacter::Heal(float HealAmount)
{
    Health = FMath::Clamp(Health + HealAmount, 0.f, MaxHealth);
}

void ANineCharacter::OnDeath()
{
}
