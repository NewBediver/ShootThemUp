// Shoot Them Up Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUCoreTypes.h"
#include "STUHealthComponent.generated.h"

class UCameraShakeBase;
class UPhysicalMaterial;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent {
    GENERATED_BODY()

  public:
    // Sets default values for this component's properties
    USTUHealthComponent();

    float GetHealth() const;

    FOnDeathSignature OnDeath;
    FOnHealthChangedSignature OnHealthChanged;

    UFUNCTION(BlueprintCallable, Category = "Health")
    bool IsDead() const;

    UFUNCTION(BlueprintCallable, Category = "Health")
    float GetHealthPercent() const;

    bool TryToAddHealth(float health_amount);
    bool IsHealthFull() const;

  protected:
    // Called when the game starts
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health",
              meta = (ClampMin = "0.0", ClampMax = "1000.0"))
    float max_health_ = 100.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
    bool auto_heal_ = true;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal",
              meta = (EditCondition = "auto_heal_"))
    float heal_update_time_ = 1.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal",
              meta = (EditCondition = "auto_heal_"))
    float heal_delay_ = 3.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal",
              meta = (EditCondition = "auto_heal_"))
    float heal_modifier_ = 5.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    TSubclassOf<UCameraShakeBase> camera_shake_;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
    TMap<UPhysicalMaterial*, float> damage_modifiers_;

  private:
    UFUNCTION()
    void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
                         class AController* InstigatedBy, AActor* DamageCauser);
    UFUNCTION()
    void OnTakePointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy,
                           FVector HitLocation, UPrimitiveComponent* FHitComponent, FName BoneName,
                           FVector ShotFromDirection, const UDamageType* DamageType,
                           AActor* DamageCauser);
    UFUNCTION()
    void OnTakeRadialDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                            FVector Origin, FHitResult HitInfo, AController* InstigatedBy,
                            AActor* DamageCauser);

    void HealUpdate();
    void SetHealth(float NewHealth);

    void PlayCameraShake();

    void Killed(AController* killer_controller);

    void ApplyDamage(float damage, AController* instigated_by);
    float GetPointDamageModifier(AActor* damaged_actor, const FName& bone_name);

    void ReportDamageEvent(float damage, AController* instigated_by);

    float health_ = 0.0f;
    FTimerHandle heal_time_handle_;
};
