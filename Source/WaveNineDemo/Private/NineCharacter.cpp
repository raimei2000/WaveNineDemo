#include "NineCharacter.h"
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

void ANineCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

}

