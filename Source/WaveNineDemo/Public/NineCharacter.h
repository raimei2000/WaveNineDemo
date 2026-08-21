#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NineCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
struct FInputActionValue;

UCLASS()
class WAVENINEDEMO_API ANineCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ANineCharacter();

    UPROPERTY(VisibleAnywhere , BlueprintReadOnly , Category = "NineCharacter|Camera")
    USpringArmComponent* SpringArm;
    UPROPERTY(VisibleAnywhere , BlueprintReadOnly , Category = "NineCharacter|Camera")
    UCameraComponent* Camera;

protected:
    UFUNCTION()
    void Move(const FInputActionValue& Value);
    UFUNCTION()
    void StartJump(const FInputActionValue& Value);
    UFUNCTION()
    void StopJump(const FInputActionValue& Value);
    UFUNCTION()
    void Look(const FInputActionValue& Value);
    UFUNCTION()
    void StartSprint(const FInputActionValue& Value);
    UFUNCTION()
    void StopSprint(const FInputActionValue& Value);

public:
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void Heal(int32 HealAmount);

private:
    float NormalSpeed;
    float SprintSpeedMultiplier;
    float SprintSpeed;

    int32 Health;
    int32 MaxHealth;

};
