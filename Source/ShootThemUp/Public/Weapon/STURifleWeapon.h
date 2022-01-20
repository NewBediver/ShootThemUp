// Shoot Them Up Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"

class USTUWeaponFXComponent;
class UNiagaraComponent;
class UNiagaraSystem;

UCLASS()
class SHOOTTHEMUP_API ASTURifleWeapon : public ASTUBaseWeapon {
    GENERATED_BODY()

  public:
    ASTURifleWeapon();

    void StartFire() override;
    void StopFire() override;

  protected:
    void BeginPlay() override;
    void MakeShot() override;
    bool GetTraceData(FVector& trace_start, FVector& trace_end) const override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float time_between_shots_ = 0.1f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float bullet_spread_ = 1.5f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float damage_amount_ = 10.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UNiagaraSystem* trace_fx_ = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FString trace_target_name_ = "TraceTarget";

    UPROPERTY(visibleAnywhere, Category = "VFX")
    USTUWeaponFXComponent* weapon_fx_component_;

  private:
    void MakeDamage(const FHitResult& hit_result);

    void InitMuzzleFX();
    void SetMuzzleFXVisibility(bool is_visible);

    void SpawnTraceFX(const FVector& trace_start, const FVector& trace_end);

    AController* GetController() const;

    FTimerHandle shot_timer_handle_;

    UPROPERTY()
    UNiagaraComponent* muzzle_fx_component_ = nullptr;
};
