// Shoot Them Up Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"

class USTUWeaponFXComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class UAudioComponent;

UCLASS()
class SHOOTTHEMUP_API ASTURifleWeapon : public ASTUBaseWeapon {
    GENERATED_BODY()

  public:
    ASTURifleWeapon();

    void StartFire() override;
    void StopFire() override;
    void Zoom(bool enabled) override;

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

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float fov_zoom_angle_ = 50.0f;

  private:
    void MakeDamage(const FHitResult& hit_result);

    void InitFX();
    void SetMuzzleFXActive(bool is_active);

    void SpawnTraceFX(const FVector& trace_start, const FVector& trace_end);

    AController* GetController() const;

    FTimerHandle shot_timer_handle_;

    UPROPERTY()
    UNiagaraComponent* muzzle_fx_component_ = nullptr;

    UPROPERTY()
    UAudioComponent* FireAudioComponent = nullptr;

    float default_camera_fov_ = 90.0f;
};
