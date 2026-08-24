#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NineCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UWidgetComponent;
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

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
    UWidgetComponent* OverheadWidget;

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

    void UpdateOverheadHP();

    virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;

public:
    UFUNCTION(BlueprintCallable)
    float GetCharacterHealth() const;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void Heal(float HealAmount);

private:
    void OnDeath();

private:
    float NormalSpeed;
    float SprintSpeedMultiplier;
    float SprintSpeed;

    float Health;
    float MaxHealth;

};
