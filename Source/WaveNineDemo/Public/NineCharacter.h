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

    virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

    void UpdateHPUI();

    void UpdateDebuffUI();

    virtual void BeginPlay() override;

public:
    UFUNCTION(BlueprintCallable)
    float GetCharacterHealth() const;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void Heal(float HealAmount);

    void ActivateSlow();

    void DeactivateSlow();

    void ActivateBlind();

    void DeactivateBlind();

    void ActivateConfuse();

    void DeactivateConfuse();

private:
    void OnDeath();

private:
    float DefaultSpringArmLength;

    float NormalSpeed;
    float CurrentSpeed;
    float SprintSpeedMultiplier;
    float SprintSpeed;

    float Health;
    float MaxHealth;

    // slow debuff
    UPROPERTY(EditAnywhere, Category = "NineCharacter|Debuff|Slow")
    float SlowDuration;
    UPROPERTY(EditAnywhere, Category = "NineCharacter|Debuff|Slow")
    float SlowFactor;
    UPROPERTY(EditAnywhere, Category = "NineCharacter|Debuff|Slow")
    int32 MaxSlowStack;
    int32 SlowStack;
    bool bSlow;
    FTimerHandle SlowTimerHandle;

    // blind debuff
    UPROPERTY(EditAnywhere, Category = "NineCharacter|Debuff|Blind")
    float BlindDuration;
    UPROPERTY(EditAnywhere, Category = "NineCharacter|Debuff|Blind")
    float DebuffSpringArmLength;
    bool bBlind;
    FTimerHandle BlindTimerHandle;

    // confusion debuff
    UPROPERTY(EditAnywhere, Category = "NineCharacter|Debuff|Confusion")
    float ConfusionDuration;
    float ConfusedDirection;
    bool bConfusion;
    FTimerHandle ConfusionTimerHandle;
};
